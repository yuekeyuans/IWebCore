#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/util/IMetaUtil.h"
#include "core/bean/IBeanTypeManage.h"
#include "core/task/unit/ITaskInstantUnit.h"
#include "IBeanJsonSerializeWare.h"

$PackageWebCoreBegin

template<typename T, typename U, bool enabled=true>
class IBeanSerializableInterface : public IBeanJsonSerializeWare, public ITaskInstantUnit<T, enabled>
{
public:
    IBeanSerializableInterface() = default;

public:
    virtual const char* getTypeName() const final;

private:
    virtual void task() final;
};

template<typename T, typename U, bool enabled>
const char* IBeanSerializableInterface<T, U, enabled>::getTypeName() const
{
    return typeid(U).name();
}

template<typename T, typename U, bool enabled>
void IBeanSerializableInterface<T, U, enabled>::task()
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
