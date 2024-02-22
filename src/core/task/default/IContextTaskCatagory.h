#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/task/ITaskCatagoryInterface.h"

$PackageWebCoreBegin

class IContextTaskCatagory : public ITaskCatagoryInterface<IContextTaskCatagory>
{
    friend class ISingletonUnit<IContextTaskCatagory>;
private:
    IContextTaskCatagory() = default;

public:
    virtual QString name() const final;
    virtual double order() const final;
};

$PackageWebCoreEnd
