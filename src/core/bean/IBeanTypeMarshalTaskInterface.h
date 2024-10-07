#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/bean/IBeanTypeManage.h"
#include "core/task/unit/ITaskWareUnit.h"
#include "IBeanTypeMarshalWare.h"

$PackageWebCoreBegin

template<typename T, typename U, bool enabled=true>
class IBeanTypeMarshalTaskInterface : public IBeanTypeMarshalWare, public ITaskWareUnit<T, enabled>
{
public:
    IBeanTypeMarshalTaskInterface() = default;

public:
    virtual const char* getTypeName() const final;

private:
    virtual QString $name() const;
    virtual QString $catagory() const;
    virtual void $task() final;
};


template<typename T, typename U, bool enabled>
const char* IBeanTypeMarshalTaskInterface<T, U, enabled>::getTypeName() const
{
    return typeid(U).name();
}

template<typename T, typename U, bool enabled>
QString IBeanTypeMarshalTaskInterface<T, U, enabled>::$name() const
{
    return IMetaUtil::getTypename<T>();
}

template<typename T, typename U, bool enabled>
QString IBeanTypeMarshalTaskInterface<T, U, enabled>::$catagory() const
{
    return "Config";
}

template<typename T, typename U, bool enabled>
void IBeanTypeMarshalTaskInterface<T, U, enabled>::$task()
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
