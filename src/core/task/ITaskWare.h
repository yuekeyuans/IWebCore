#pragma once

#include "base/IHeaderUtil.h"

$PackageWebCoreBegin

class ITaskWare
{
    $AsWare
public:
    ITaskWare() = default;

public:
    virtual QString name() const = 0;
    virtual void task() = 0;
    virtual QString catagory() const = 0;
    virtual QStringList orders() const;
};

$PackageWebCoreEnd
