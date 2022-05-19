#pragma once

#include "base/IHeaderUtil.h"
#include "bean/IBeanWare.h"
#include "bean/ITypeManage.h"
#include "task/IStaticInitializeTaskUnit.h"

$PackageWebCoreBegin

template<class T, bool enabled = true>
class IBeanInterface : public IBeanWare, public IStaticInitializeTaskUnit<T, enabled>
{
    $UseWare
public:
    IBeanInterface() = default;
    virtual ~IBeanInterface() = default;

public:
    virtual void task() final;
};

template<typename T, bool enabled>
void IBeanInterface<T, enabled>::task()
{
    if(enabled){
        static std::once_flag initRegisterFlag;
        std::call_once(initRegisterFlag, [](){
            ITypeManage::registerBeanType(typeid (T).name());   // register type
            T::web_core_init_registerMetaType();                // register meta type
        });
    }
}

$PackageWebCoreEnd
