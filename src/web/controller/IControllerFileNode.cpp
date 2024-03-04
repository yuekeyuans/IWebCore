#include "IControllerFileNode.h"
#include "core/base/IFileUtil.h"
#include "web/IWebAssert.h"

$PackageWebCoreBegin

$UseAssert(IWebAssert)

namespace IControllerFileNodeHelper
{
    void mountFilesToServer(QHash<QString, QString>& hash, const QString& path, const QString& prefix);
    void mountFirstPageToServer(QHash<QString, QString>& hash, const QString& path, const QString& prefix);
    bool mountFilePageToServer(QHash<QString, QString>& hash, const QString& filePath, const QString& url);
}

bool IControllerFileNode::isUrlExist(const QString &url) const
{
    return this->m_enabled && m_urlFileHash.contains(url);
}

QString IControllerFileNode::getFilePath(const QString &url) const
{
    if(isUrlExist(url)){
        auto path = m_urlFileHash[url];
        if(IFileUtil::isFileExist(path)){
            return path;
        }

         m_urlFileHash.remove(url);
    }

    return getUnRegisteredFilePath(url);   // 理论上再监测一层， 方便于计算
}

void IControllerFileNode::mountMapping(const QString &dir, const QString &prefix)
{
    IControllerFileNodeHelper::mountFilesToServer(m_urlFileHash, dir, prefix);
    this->m_enabled = true;
//    travelPrint();
}

void IControllerFileNode::travelPrint(int space) const
{
    if(space == 0){
        qDebug() << "============== file mapping begin =============";
    }

    auto keys = m_urlFileHash.keys();
    for(const auto& key : keys){
        qDebug() << key << m_urlFileHash[key];
    }

    if(space == 0){
        qDebug() << "============== file mapping end =============";
    }
}

QString IControllerFileNode::getUnRegisteredFilePath(QString url) const
{
    auto keys = m_urlPrefixMap.keys();
    for(const auto& path : keys){
        auto prefix = m_urlPrefixMap[path];
        if(url.startsWith(prefix)){
            auto filePath = IFileUtil::joinPath(path, url.replace(prefix, ""));
            if(QFileInfo(filePath).exists()){
                m_urlFileHash[url] = filePath;          // NOTE: 这里线程不安全，但是理论上没啥问题，因为他可以请求不成功
                return filePath;
            }
        }
    }
    return {};
}

void IControllerFileNodeHelper::mountFilesToServer(QHash<QString, QString>& hash, const QString &path, const QString &prefix)
{
    QDir dir(path);
    if(!dir.exists() || dir.isEmpty()){
        return;
    }

    mountFirstPageToServer(hash, path, prefix);

    dir.setFilter(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot);
    auto entries = dir.entryInfoList();
    for(const auto& entry : entries){
        if(entry.isDir()){
            auto newPrefix = IFileUtil::joinPath(prefix, entry.fileName());
            mountFilesToServer(hash, entry.absoluteFilePath(), newPrefix);
            continue;
        }

        QString url = IFileUtil::joinPath(prefix, entry.fileName());
        while(url.contains("//")){
            url.replace("//", "/");
        }

        auto filePath = entry.absoluteFilePath();
        mountFilePageToServer(hash, filePath, url);
    }
}

void IControllerFileNodeHelper::mountFirstPageToServer(QHash<QString, QString>& hash, const QString& path, const QString& prefix)
{
    static const QStringList names = {
        "index.html", "index.htm", "default.html", "default.html", "home.html", "home.htm"
    };

    for(const auto& name : names){
        auto pagePath = IFileUtil::joinPath(path, name);
        if(mountFilePageToServer(hash, pagePath, prefix)){
            return;
        }
    }
}

bool IControllerFileNodeHelper::mountFilePageToServer(QHash<QString, QString>& hash, const QString& filePath, const QString& url)
{
    bool alreadyExist = hash.contains(url);
    if(QFileInfo(filePath).exists()){
        if(!alreadyExist){
            hash[url] = filePath;
            return true;
        }

        IAssertInfo info;
        info.reason = QString("url: ").append(url).append(" path1: ").append(filePath).append(" path2: ").append(hash[url]);
        $Ast->fatal("register_the_same_url", info);
    }
    return false;
}

$PackageWebCoreEnd
