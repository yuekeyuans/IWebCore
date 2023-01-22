#pragma once

#include <IWebCore>
#include "core/task/ITaskWare.h"
#include "core/task/ITaskManage.h"

template<typename T, bool enabled=true>
class ResourceTaskInterface : public ITaskWare, public IRegisterInstanceUnit<T, true>
{
public:
    ResourceTaskInterface() = default;

public:
    virtual void registerToBase() final;
};

template<typename T, bool enabled>
void ResourceTaskInterface<T, enabled>::registerToBase()
{
    ITaskManage::instance()->addTaskWare(T::instance());
}
