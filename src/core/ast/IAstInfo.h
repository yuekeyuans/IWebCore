#pragma once

#include "base/IHeaderUtil.h"

$PackageWebCoreBegin

class IAstInfo
{
public:
    IAstInfo() = default;

    operator QString() const;

public:
    int line{INT_MIN};
    QString file;
    QString reason;
    QString className;
    QString function;
    QString returnType;
    QString paramterType;
    QString parameterName;
};

$PackageWebCoreEnd
