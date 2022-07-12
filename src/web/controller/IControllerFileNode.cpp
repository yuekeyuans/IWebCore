#include "IControllerFileNode.h"

$PackageWebCoreBegin

bool IControllerFileNode::isUrlExist(const QString &url) const
{
    for(const auto& pair : m_nodes){
        const auto& prefix = pair.first;
        if(!prefix.isEmpty()){
            if(!url.startsWith(prefix)){
                continue;
            }
        }

        const auto& path = pair.second;
        auto filePath =  QString(url).replace(prefix, "").prepend(path);
        if(QFile(filePath).exists()){
            return true;
        }
    }
    return false;
}

QString IControllerFileNode::getFilePath(const QString &url) const
{
    for(const auto& pair : m_nodes){
        const auto& prefix = pair.first;
        if(!prefix.isEmpty()){
            if(!url.startsWith(prefix)){
                continue;
            }
        }

        const auto& path = pair.second;
        auto filePath =  QString(url).replace(prefix, "").prepend(path);
        QFileInfo fileInfo(filePath);
        if(fileInfo.exists() && fileInfo.isFile()){
            return filePath;
        }
    }
    return {};
}

void IControllerFileNode::mountFilesToServer(const QString &path, const QString &prefix)
{
    // TODO: need check whether conflict?

    // TODO: need to sort by prefix length reverse in order to acclerate speed
    m_nodes.append({prefix, path});
}

$PackageWebCoreEnd
