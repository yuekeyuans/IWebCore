#pragma once

#include "core/task/default/IInitializationTaskInterface.h"

$PackageWebCoreBegin

class INodyTemplateTask : public IInitializationTaskInterface<INodyTemplateTask>
{
public:
    INodyTemplateTask();

public:
    virtual void task() final;
};

$PackageWebCoreEnd
