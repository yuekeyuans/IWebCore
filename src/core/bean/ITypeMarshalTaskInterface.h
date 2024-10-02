#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/bean/IBeanTypeManage.h"
#include "core/task/unit/ITaskWareUnit.h"
#include "ITypeMarshalWare.h"

$PackageWebCoreBegin

template<typename T, typename U, bool enabled=true>
class ITypeMarshalTaskInterface
    : public ITypeMarshalWare, public ITaskWareUnit<T, enabled>
{
public:
    ITypeMarshalTaskInterface() = default;

public:
    virtual const char* getTypeName() const final;

private:
    virtual QString name() const;
    virtual QString catagory() const;
    virtual void task() final;
};

template<typename T, typename U, bool enabled>
const char* ITypeMarshalTaskInterface<T, U, enabled>::getTypeName() const
{
    return typeid(U).name();
}

template<typename T, typename U, bool enabled>
QString ITypeMarshalTaskInterface<T, U, enabled>::name() const
{
    return IMetaUtil::getTypename<T>();
}

template<typename T, typename U, bool enabled>
QString ITypeMarshalTaskInterface<T, U, enabled>::catagory() const
{
    return "Config";
}

template<typename T, typename U, bool enabled>
void ITypeMarshalTaskInterface<T, U, enabled>::task()
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
