#pragma once

#include <IWebCore>
#include "ResourceTaskInterface.h"

class ResourceLoader : public ResourceTaskInterface<ResourceLoader>
{
    $UseInstance(ResourceLoader)
private:
    ResourceLoader() = default;

public:
    virtual QString name() const final;
    virtual QStringList orders() const final;
    virtual QString catagory() const final;
    virtual void task() final;
};

