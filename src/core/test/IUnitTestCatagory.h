#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/task/ITaskCatagoryInterface.h"

$PackageWebCoreBegin

class IUnitTestCatagory : public ITaskCatagoryInterface<IUnitTestCatagory>
{
public:
    virtual double $order() const final;
};

inline double IUnitTestCatagory::$order() const
{
    return 99;
}

$PackageWebCoreEnd
