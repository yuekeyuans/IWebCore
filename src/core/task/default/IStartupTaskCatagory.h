﻿#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/task/ITaskCatagoryInterface.h"

$PackageWebCoreBegin

class IStartupTaskCatagory : public ITaskCatagoryInterface<IStartupTaskCatagory>
{
private:
    virtual QString name() const final;
    virtual double order() const final;
};

$PackageWebCoreEnd


