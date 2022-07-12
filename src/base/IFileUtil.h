#pragma once
#include "base/IHeaderUtil.h"

$PackageWebCoreBegin

namespace IFileUtil {

    bool isFileExist(const QString& path);

    QString readFileAsString(const QString& path, bool *ok=nullptr);
    QByteArray readFileAsByteArray(const QString& path, bool*ok=nullptr);
}

$PackageWebCoreEnd
