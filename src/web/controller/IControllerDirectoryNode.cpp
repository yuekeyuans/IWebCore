#include "IControllerDirectoryNode.h"
#include "web/IWebAssert.h"

$PackageWebCoreBegin

$UseAssert(IWebAssert)

bool IControllerDirectoryNode::isEnabled() const
{
    return m_enabled;
}

QString IControllerDirectoryNode::getFilePath(const QString &url) const
{
    if(!m_enabled){
        return {};
    }

    auto values = m_map.values();
    for(const QString& val : values){
        if(url.startsWith(val)){
            auto key = m_map.key(val);
            QString path = key.append(QString(url).replace(val, ""));
            if(QFileInfo(path).exists()){
                return path;
            }
        }
    }

    return {};
}

void IControllerDirectoryNode::mountMapping(const QString &path, const QString &prefix)
{
    QDir dir(path);
    if(!dir.exists() || dir.isEmpty()){
        $Ast->warn("static_file_dir_not_exist");
        return;
    }

    auto dirPath = dir.absolutePath().append("/").replace("//", "/");
    auto url = QString(prefix).append("/").replace("//", "/");
    m_map[dirPath] = url;
    m_enabled = true;
}

void IControllerDirectoryNode::travelPrint() const
{
    if(m_enabled){
        qDebug() << "Free Mapping Directory";
        auto keys = m_map.keys();
        for(const auto& key : keys){
            qDebug().noquote()<< QString().fill(' ', 2) << key << "to" << m_map[key];
        }
        qDebug() << "";
    }
}

$PackageWebCoreEnd
