#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/util/IMetaUtil.h"
#include "core/bean/IBeanTypeManage.h"
#include "core/task/unit/ITaskInstantUnit.h"
#include "ITypeMarshalWare.h"

$PackageWebCoreBegin

template<typename T, typename U, bool enabled=true>
class ITypeMarshalInterface : public ITypeMarshalWare, public ITaskInstantUnit<T, enabled>
{
public:
    ITypeMarshalInterface() = default;

public:
    virtual const char* getTypeName() const final;

private:
    virtual void task() final;
};

template<typename T, typename U, bool enabled>
const char* ITypeMarshalInterface<T, U, enabled>::getTypeName() const
{
    return typeid(U).name();
}

template<typename T, typename U, bool enabled>
void ITypeMarshalInterface<T, U, enabled>::task()
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
