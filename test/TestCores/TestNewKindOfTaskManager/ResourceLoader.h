#pragma once

#include <IWebCore>
#include "ResourceTaskInterface.h"

class ResourceLoader : public ResourceTaskInterface<ResourceLoader>
{
    $UseInstance(ResourceLoader)
public:
    ResourceLoader();

    virtual QString name() final;
    virtual QStringList orders() final;
    virtual void task() final;
    virtual QString catagory() final;
};

