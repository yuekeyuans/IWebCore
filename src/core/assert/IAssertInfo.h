#pragma once

#include "core/base/IHeaderUtil.h"

$PackageWebCoreBegin

class IAssertInfo
{
public:
    IAssertInfo() = default;

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
