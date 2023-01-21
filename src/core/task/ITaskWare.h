#pragma once

#include "base/IHeaderUtil.h"
$PackageWebCoreBegin

class ITaskWare
{
    $AsWare
public:
    ITaskWare() = default;

public:
    virtual QString name() = 0;
    virtual void task() = 0;
    virtual QString catagory() = 0;
    virtual QStringList orders();
    virtual void printTips();
};

$PackageWebCoreEnd
