#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/task/ITaskCatagoryInterface.h"

$PackageWebCoreBegin

class IConfigTaskCatagory : public ITaskCatagoryInterface<IConfigTaskCatagory>
{
    friend class ISingletonUnit<IConfigTaskCatagory>;
private:
    IConfigTaskCatagory() = default;

public:
    virtual QString name() const final;
    virtual double order() const final;
};

$PackageWebCoreEnd
