#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/task/default/IInitializationTaskInterface.h"

$PackageWebCoreBegin

class IWebDefaultProfileTask : public IInitializationTaskInterface<IWebDefaultProfileTask>
{
public:
    IWebDefaultProfileTask() = default;

public:
    virtual double order() const final;
    virtual void task() final;

};

$PackageWebCoreEnd
