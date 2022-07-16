#include "IControllerFileNode.h"
#include "base/IFileUtil.h"
#include "web/IWebAssert.h"

$PackageWebCoreBegin

$UseAssert(IWebAssert)

namespace IControllerFileNodeHelper{
    void mountStaticFileToServer(QHash<QString, QString>& hash, const QString& path, const QString& prefix);

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

    dir.setFilter(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot);
    auto entries = dir.entryInfoList();
    for(const auto& entry : entries){
        if(entry.isDir()){
            auto newPrefix = IFileUtil::joinPath(prefix, entry.fileName());
            mountStaticFileToServer(hash, entry.absoluteFilePath(), newPrefix);
            continue;
        }

        auto url = IFileUtil::joinPath(prefix, entry.fileName());
        if(hash.contains(url)){
            IAssertInfo info;
            info.reason = QString("url: ").append(url)
                              .append(" path1: ").append(entry.absoluteFilePath())
                              .append(" path2: ").append(hash[url]);

            $Ast->fatal("register_the_same_url", info);
        }
        hash[url] = entry.absoluteFilePath();
    }
}

$PackageWebCoreEnd
