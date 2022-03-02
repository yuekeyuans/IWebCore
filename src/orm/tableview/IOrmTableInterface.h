#pragma once

#include "base/IHeaderUtil.h"
#include "orm/tableview/IOrmTableWare.h"
#include "common/task/IStaticInitializeTaskUnit.h"
#include "common/type/ITypeManage.h"

$PackageWebCoreBegin

template<typename T, bool enabled = true>
class IOrmTableInterface : public IOrmTableWare, public IStaticInitializeTaskUnit<T, enabled>
{
public:
    IOrmTableInterface() = default;
    virtual ~IOrmTableInterface() = default;

public:
    virtual void task() override;
};

template<typename T, bool enabled>
void IOrmTableInterface<T, enabled>::task(){
    if(enabled){
        static std::once_flag initRegisterFlag;
        std::call_once(initRegisterFlag, [](){
            ITypeManage::registerBeanType(typeid (T).name());   // register type
            T::web_core_init_registerMetaType();                // register meta type
        });
    }
}

$PackageWebCoreEnd
