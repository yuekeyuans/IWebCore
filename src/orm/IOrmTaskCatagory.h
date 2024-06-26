﻿#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/task/ITaskCatagoryInterface.h"

$PackageWebCoreBegin

class IOrmTaskCatagory : public ITaskCatagoryInterface<IOrmTaskCatagory>
{
public:
    virtual QString name() const final;
    virtual double order() const final;
};

$PackageWebCoreEnd
