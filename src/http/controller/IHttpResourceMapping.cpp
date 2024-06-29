﻿#include "IHttpResourceMapping.h"
#include "core/base/IFileUtil.h"
#include "http/controller/IControllerAbort.h"

$PackageWebCoreBegin

namespace IControllerResourceNodeHelper
{
    void mountFilesToResourceMapping(QMap<QString, QString>& hash, const QString& path, const QString& prefix);
    void mountFirstPageToServer(QMap<QString, QString>& hash, const QString& path, const QString& prefix);
    bool mountFilePageToServer(QMap<QString, QString>& hash, const QString& filePath, const QString& url);
}

bool IHttpResourceMapping::isEnabled() const
{
    return m_enabled;
}

QString IHttpResourceMapping::getFilePath(IStringView url) const
{
    // TODO: optimize latter
    auto newUrl = url.toQString();
    if(m_enabled && m_fileMappings.contains(newUrl)){
        return m_fileMappings[newUrl];
    }

    return {};
}

QStringList IHttpResourceMapping::getFileEntries(const QString &url)
{
    if(!m_enabled){
        return {};
    }

    QStringList ret;
    static const auto keys = m_fileMappings.keys();
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

void IHttpResourceMapping::mountMapping(const QString &dir, const QString &prefix)
{
    m_map[dir] = prefix;
    this->m_enabled = true;
    IControllerResourceNodeHelper::mountFilesToResourceMapping(m_fileMappings, dir, prefix);
}

void IHttpResourceMapping::travelPrint() const
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

// NOTE: 写的有点啰嗦，先这样吧
// TODO: check warn
void IControllerResourceNodeHelper::mountFilesToResourceMapping(QMap<QString, QString>& hash, const QString &path, const QString &prefix)
{
    QDir dir(path);
    if(!dir.exists() || dir.isEmpty()){
//        $Ast->warn("static_file_dir_not_exist");
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

void IControllerResourceNodeHelper::mountFirstPageToServer(QMap<QString, QString>& hash, const QString& path, const QString& prefix)
{
    static $QStringList defaultPages{"http.defaultPageNames"};
    static const QStringList pages = defaultPages.value();
    for(const auto& name : pages){
        auto pagePath = IFileUtil::joinPath(path, name);
        if(mountFilePageToServer(hash, pagePath, prefix)){
            return;
        }
    }
}

bool IControllerResourceNodeHelper::mountFilePageToServer(QMap<QString, QString>& hash, const QString& filePath, const QString& url)
{
    bool alreadyExist = hash.contains(url);
    if(QFileInfo(filePath).exists()){
        if(!alreadyExist){
            hash[url] = filePath;
            return true;
        }
        IControllerAbort::abortregister_the_same_url(QString("url: ").append(url).append(" path1: ").append(filePath).append(" path2: ").append(hash[url]), $ISourceLocation);
    }
    return false;
}

$PackageWebCoreEnd
