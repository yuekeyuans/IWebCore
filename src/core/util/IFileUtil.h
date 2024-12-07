#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/base/IResult.h"

$PackageWebCoreBegin

namespace IFileUtil
{
    bool isFileExist(const QString& path);

    QString readFileAsString(const QString& path, bool& ok);
    IResult<QString> readFileAsString(const QString& path);

    QByteArray readFileAsByteArray(const QString& path, bool* ok=nullptr);

    QString getFileSuffix(const QString& path);

    template<typename T>
    QString joinPath(const T& first);

    template<typename T, typename...Args>
    QString joinPath(const T&first, const Args&...rest);

    void assertWhenFileInvalid(const QString& path);
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
    return QFileInfo(path).absoluteFilePath();
}

$PackageWebCoreEnd

