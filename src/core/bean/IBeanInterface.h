#pragma once

#include "IBeanWare.h"
#include "ITypeManage.h"
#include "base/IHeaderUtil.h"
#include "core/bean/IBeanPreProcessor.h"
#include "core/task/unit/IStaticInitializeTaskUnit.h"

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
            IBeanTypeManage::registerBeanType(typeid (T).name());   // register type
            T::web_core_init_registerMetaType();                // register meta type
        });
    }
}

$PackageWebCoreEnd
