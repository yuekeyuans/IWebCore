#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/config/IProfileManage.h"
#include "core/config/IConfigTaskCatagory.h"
#include "core/task/unit/ITaskWareUnit.h"
#include "core/unit/ISingletonUnit.h"

$PackageWebCoreBegin

template<typename T, bool enabled=true>
class IProfileTaskInterface : public ITaskWareUnit<T, IConfigTaskCatagory, enabled>, public ISingletonUnit<T>
{
public:
    IProfileTaskInterface() = default;

public:
    virtual IJson config() = 0;
    virtual std::string path() const;

protected:
    virtual void $task() final;
};

template<typename T, bool enabled>
std::string IProfileTaskInterface<T, enabled>::path() const
{
    return {};
}

template<typename T, bool enabled>
void IProfileTaskInterface<T, enabled>::$task()
{
    auto value = config();
    if(!value.is_null()){
        IProfileManage::instance()->addConfig(value, path());
    }
}

$PackageWebCoreEnd
