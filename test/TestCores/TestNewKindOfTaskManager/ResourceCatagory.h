#pragma once

#include <IWebCore>
#include "core/task/ITaskCatagoryInterface.h"

class ResourceCatagory : public ITaskCatagoryInterface<ResourceCatagory>
{
public:
    ResourceCatagory() = default;

public:
    virtual QString name() const final;
};

