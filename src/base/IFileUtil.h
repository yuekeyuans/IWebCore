#pragma once
#include "base/IHeaderUtil.h"

$PackageWebCoreBegin

namespace IFileUtil {
    QString readFile(QFile& file);
    QString readFile(const QString& path);

    bool isFileExist(const QString& path);
}

$PackageWebCoreEnd
