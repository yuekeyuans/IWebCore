#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/task/ITaskCatagoryInterface.h"

$PackageWebCoreBegin

class IHttpControllerTaskCatagory : public ITaskCatagoryInterface<IHttpControllerTaskCatagory>
{
public:
    virtual QString $name() const final;
};

$PackageWebCoreEnd
