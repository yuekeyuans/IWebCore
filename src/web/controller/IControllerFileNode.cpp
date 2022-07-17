#include "IControllerFileNode.h"
#include "base/IFileUtil.h"
#include "web/IWebAssert.h"

$PackageWebCoreBegin

$UseAssert(IWebAssert)

namespace IControllerFileNodeHelper{
    void mountStaticFileToServer(QHash<QString, QString>& hash, const QString& path, const QString& prefix);
    void mountFirstPageToServer(QHash<QString, QString>& hash, const QString& path, const QString& prefix);

    bool enabled {false};
}


bool IControllerFileNode::isUrlExist(const QString &url) const
{
    if(IControllerFileNodeHelper::enabled){
        return m_urlFileHash.contains(url);
    }
    return false;
}

QString IControllerFileNode::getFilePath(const QString &url) const
{
    if(IControllerFileNodeHelper::enabled && isUrlExist(url)){
        return m_urlFileHash[url];
    }
    return {};
}

void IControllerFileNode::mountFilesToServer(const QString &path, const QString &prefix)
{
    if(path.startsWith(":/")){
        // TODO:
    }else{
        IControllerFileNodeHelper::mountStaticFileToServer(m_urlFileHash, path, prefix);
//        IControllerFileNodeHelper::watcher.addPath(path);
//        IControllerFileNodeHelper::watcher.
    }

    IControllerFileNodeHelper::enabled = true;
}

void IControllerFileNodeHelper::mountStaticFileToServer(QHash<QString, QString>& hash, const QString &path, const QString &prefix)
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
            mountStaticFileToServer(hash, entry.absoluteFilePath(), newPrefix);
            continue;
        }

        auto url = IFileUtil::joinPath(prefix, entry.fileName());
        if(!hash.contains(url)){
            hash[url] = entry.absoluteFilePath();
            continue;
        }

        // abort
        IAssertInfo info;
        info.reason = QString("url: ").append(url)
                          .append(" path1: ").append(entry.absoluteFilePath()).append(" path2: ").append(hash[url]);
        $Ast->fatal("register_the_same_url", info);

    }
}

void IControllerFileNodeHelper::mountFirstPageToServer(QHash<QString, QString>& hash, const QString& path, const QString& prefix)
{
    static const QStringList names = {
        "index.html", "index.htm", "default.html", "default.html", "home.html", "home.htm"
    };

    bool alreadyExist = hash.contains(prefix);
    for(const auto& name : names){
        auto pagePath = IFileUtil::joinPath(path, name);
        if(QFileInfo(pagePath).exists()){
            if(!alreadyExist){
                hash[prefix] = pagePath;        // 按照 names 排序
                return;
            }

            IAssertInfo info;
            info.reason = QString("url: ").append(prefix)
                              .append(" path1: ").append(pagePath).append(" path2: ").append(hash[prefix]);
            $Ast->fatal("register_the_same_url", info);
        }
    }
}

$PackageWebCoreEnd
