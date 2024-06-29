#pragma once

#include "core/util/IHeaderUtil.h"

$PackageWebCoreBegin

class IHttpTestTool
{
public:
    IHttpTestTool() = default;

public:
    QString createRandomFile(QString fileName="", int fileSize=1024);
};

$PackageWebCoreEnd
