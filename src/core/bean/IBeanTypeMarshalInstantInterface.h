#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/bean/IBeanTypeManage.h"
#include "core/task/unit/ITaskInstantUnit.h"
#include "IBeanTypeMarshalWare.h"

$PackageWebCoreBegin

template<typename T, typename U, bool enabled=true>
class IBeanTypeMarshalInstantInterface : public IBeanTypeMarshalWare, public ITaskInstantUnit<T, enabled>
{
public:
    IBeanTypeMarshalInstantInterface() = default;

public:
    virtual const char* getTypeName() const final;

private:
    virtual void $task() final;
};

template<typename T, typename U, bool enabled>
const char* IBeanTypeMarshalInstantInterface<T, U, enabled>::getTypeName() const
{
    return typeid(U).name();
}

template<typename T, typename U, bool enabled>
void IBeanTypeMarshalInstantInterface<T, U, enabled>::$task()
{
    if constexpr (enabled){
        static std::once_flag flag;
        std::call_once(flag, [=](){
            static T value{};
            IBeanTypeManage::instance()->registerSerializeWare(&value);
        });
    }
}

$PackageWebCoreEnd
