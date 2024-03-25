#include "IControllerResourceMapping.h"
#include "core/base/IFileUtil.h"
#include "web/IWebAssert.h"

$PackageWebCoreBegin

$UseAssert(IWebAssert)

namespace IControllerResourceNodeHelper
{
    void mountFilesToResourceMapping(QHash<QString, QString>& hash, const QString& path, const QString& prefix);
    void mountFirstPageToServer(QHash<QString, QString>& hash, const QString& path, const QString& prefix);
    bool mountFilePageToServer(QHash<QString, QString>& hash, const QString& filePath, const QString& url);
}

bool IControllerResourceMapping::isEnabled() const
{
    return m_enabled;
}

QString IControllerResourceMapping::getFilePath(const QString &url) const
{
    if(m_enabled && m_fileMappings.contains(url)){
        return m_fileMappings[url];
    }
    return {};
}

void IControllerResourceMapping::mountMapping(const QString &dir, const QString &prefix)
{
    m_map[dir] = prefix;
    this->m_enabled = true;
    IControllerResourceNodeHelper::mountFilesToResourceMapping(m_fileMappings, dir, prefix);
}

void IControllerResourceMapping::travelPrint() const
{
    if(m_enabled){
        qDebug() << "Resource Mapping:";
        auto keys = m_map.keys();
        for(const auto& key : keys){
            qDebug().noquote()<< QString().fill(' ', 2) << key << "to" << m_map[key];
        }
        qDebug() << "";
    }
}

void IControllerResourceNodeHelper::mountFilesToResourceMapping(QHash<QString, QString>& hash, const QString &path, const QString &prefix)
{
    QDir dir(path);
    if(!dir.exists() || dir.isEmpty()){
        $Ast->warn("static_file_dir_not_exist");
        return;
    }

    mountFirstPageToServer(hash, path, prefix);
    dir.setFilter(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot);
    auto entries = dir.entryInfoList();
    for(const auto& entry : entries){
        if(entry.isDir()){
            auto newPrefix = IFileUtil::joinPath(prefix, entry.fileName());
            mountFilesToResourceMapping(hash, entry.absoluteFilePath(), newPrefix);
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

void IControllerResourceNodeHelper::mountFirstPageToServer(QHash<QString, QString>& hash, const QString& path, const QString& prefix)
{
//    static const QStringList names = {
//        "index.html", "index.htm", "default.html", "default.html", "home.html", "home.htm"
//    };

    for(const auto& name : IConstantUtil::IndexPageNames){
        auto pagePath = IFileUtil::joinPath(path, name);
        if(mountFilePageToServer(hash, pagePath, prefix)){
            return;
        }
    }
}

bool IControllerResourceNodeHelper::mountFilePageToServer(QHash<QString, QString>& hash, const QString& filePath, const QString& url)
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
