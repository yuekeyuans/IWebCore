#pragma once

#include "base/IHeaderUtil.h"
#include "common/task/IStaticInitializeTaskUnit.h"
#include "common/type/ITypeManage.h"
#include "orm/tableview/IOrmViewWare.h"

$PackageWebCoreBegin

template<typename T, bool enabled=true>
class IOrmViewInterface : public IOrmViewWare, public IStaticInitializeTaskUnit<T, enabled>
{
    $UseWare
public:
    IOrmViewInterface() = default;
    virtual ~IOrmViewInterface() = default;

public:
    virtual void task() final;
    virtual const IOrmViewInfo& getViewInfo() const override = 0;
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
