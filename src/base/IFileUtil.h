#pragma once
#include "base/IHeaderUtil.h"

$PackageWebCoreBegin

namespace IFileUtil {

    bool isFileExist(const QString& path);

    QString readFileAsString(const QString& path, bool *ok=nullptr);

    QByteArray readFileAsByteArray(const QString& path, bool*ok=nullptr);

    QString normalizeFilePath(QString path, bool*ok=nullptr);

    template<typename T>
    QString joinPath(const T& first);

    template<typename T, typename...Args>
    QString joinPath(const T&first, const Args&...rest);

    QString getFileSuffix(const QString& path);
}

template<typename T>
QString IFileUtil::joinPath(const T &first)
{
    return first;
}

template<typename T, typename ... Args>
QString IFileUtil::joinPath(const T &first, const Args &...rest)
{
    auto path = QString(first).append("/").append(joinPath(rest...));
    return normalizeFilePath(path);   // ignore error
}

$PackageWebCoreEnd
