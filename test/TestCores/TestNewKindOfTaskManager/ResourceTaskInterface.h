#pragma once

#include <IWebCore>
#include "core/task/ITaskWare.h"

template<typename T, bool enabled=true>
class ResourceTaskInterface : public ITaskWare, public IRegisterInstanceUnit<T, true>
{
    $UseWare
public:
    ResourceTaskInterface() = default;

public:
    virtual void registerToBase() final;
};

template<typename T, bool enabled>
void ResourceTaskInterface<T, enabled>::registerToBase()
{
    qDebug() << "register this class to basic";
}
