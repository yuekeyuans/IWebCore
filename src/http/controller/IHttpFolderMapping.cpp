#include "IHttpFolderMapping.h"

$PackageWebCoreBegin

bool IHttpFolderMapping::isEnabled() const
{
    return m_enabled;
}

QString IHttpFolderMapping::getFilePath(IStringView url_) const
{
    if(!m_enabled){
        return {};
    }

    // TODO: optimize latter
    auto url = url_.toQString();
    auto values = m_map.values();
    for(const QString& val : values){
        if(url.startsWith(val)){
            auto key = m_map.key(val);
            QString path = key.append(QString(url).replace(val, ""));
            QFileInfo info(path);
            if(info.exists() && info.isFile()){
                return path;
            }
            if(info.exists() && info.isDir()){
                return getFolderDefaultFilePath(path);
            }
        }
    }

    return {};
}

QStringList IHttpFolderMapping::getFileEntries(const QString &url)
{
    if(!m_enabled){
        return {};
    }

    QStringList ret;
    auto keys = m_map.keys();
    for(const QString& key : keys){
        if(key.startsWith(url)){
            auto val = key.mid(url.length());
            if(!val.contains("/")){
                ret.append(val);
            }
        }
    }
    return ret;
}

void IHttpFolderMapping::mountMapping(const QString &path, const QString &prefix)
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

void IHttpFolderMapping::travelPrint() const
{
    if(m_enabled){
        qDebug() << "Folder Mapping:";
        auto keys = m_map.keys();
        for(const auto& key : keys){
            qDebug().noquote()<< QString().fill(' ', 2) << key << "to" << m_map[key];
        }
        qDebug() << "";
    }
}

QString IHttpFolderMapping::getFolderDefaultFilePath(const QString &path) const
{
    static const QStringList& pages = defaultPages.value();
    for(const QString& name : pages){
        QFileInfo file(path + name);
        if(file.exists() && file.isFile()){
            return file.absoluteFilePath();
        }
    }
    return {};
}

$PackageWebCoreEnd
