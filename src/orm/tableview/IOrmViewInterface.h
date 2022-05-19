#pragma once

#include "base/IHeaderUtil.h"
#include "bean/ITypeManage.h"
#include "orm/tableview/IOrmViewWare.h"
#include "task/IStaticInitializeTaskUnit.h"

$PackageWebCoreBegin

template<typename T, bool enabled=true>
class IOrmViewInterface : public IOrmViewWare, public IStaticInitializeTaskUnit<T, enabled>
{
    $UseWare
public:
    IOrmViewInterface() = default;
    virtual ~IOrmViewInterface() = default;

    // NOTE: 目前没有对 View 进行的特殊操作，所有的操作在基类当中进行。

public:
    virtual void task() final;
    virtual const IOrmViewInfo* getOrmEntityInfo() const override = 0;
};

template<typename T, bool enabled>
void IOrmViewInterface<T, enabled>::task(){
    if(enabled){
        static std::once_flag initRegisterFlag;
        std::call_once(initRegisterFlag, [](){
            ITypeManage::registerBeanType(typeid (T).name());   // register type
            T::web_core_init_registerMetaType();                // register meta type
        });
    }
}

$PackageWebCoreEnd
