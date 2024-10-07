#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/util/IMetaUtil.h"
#include "core/bean/IBeanTypeManage.h"
#include "core/task/unit/ITaskInstantUnit.h"
#include "orm/tableview/IOrmViewWare.h"

$PackageWebCoreBegin

template<typename T, bool enabled=true>
class IOrmViewInterface : public IOrmViewWare, public ITaskInstantUnit<T, enabled>
{
public:
    IOrmViewInterface() = default;
    virtual ~IOrmViewInterface() = default;

public:
    virtual QString $name() const override;
    virtual const char* $catagory() const final;
    virtual void $task() final;
    virtual const IOrmViewInfo* getOrmEntityInfo() const override = 0;
};

template<typename T, bool enabled>
QString IOrmViewInterface<T, enabled>::$name() const
{
    return IMetaUtil::getMetaClassName(T::staticMetaObject);
}

template<typename T, bool enabled>
QString IOrmViewInterface<T, enabled>::$catagory() const
{
    return "Orm";
}

template<typename T, bool enabled>
void IOrmViewInterface<T, enabled>::$task(){
    if constexpr (enabled){
        static std::once_flag initRegisterFlag;
        std::call_once(initRegisterFlag, [](){
            IBeanTypeManage::registerBeanType(typeid (T).name());   // register type
            T::web_core_init_registerMetaType();                // register meta type
        });
    }
}

$PackageWebCoreEnd
