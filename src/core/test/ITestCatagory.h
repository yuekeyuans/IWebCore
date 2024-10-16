﻿#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/task/ITaskCatagoryInterface.h"

$PackageWebCoreBegin

class ITestCatagory : public ITaskCatagoryInterface<ITestCatagory>
{
public:
    virtual const char* $catagory() const final;
    virtual double $order() const final;
};

$PackageWebCoreEnd
