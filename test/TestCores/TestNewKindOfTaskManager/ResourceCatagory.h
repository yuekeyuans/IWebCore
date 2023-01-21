#pragma once

#include <IWebCore>
#include "core/task/ITaskCatagoryInterface.h"

class ResourceCatagory : public ITaskCatagoryInterface<ResourceCatagory>
{
    $UseInstance(ResourceCatagory)
public:
    ResourceCatagory();

    virtual QString name() final;
};

