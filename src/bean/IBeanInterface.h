#pragma once

#include "base/IHeaderUtil.h"
#include "bean/IBeanWare.h"
#include "common/task/IStaticInitializeTaskUnit.h"
#include "common/support/IRegisterMetaTypeUnit.h"
#include "common/support/IRegisterTypeUnit.h"
#include "common/type/ITypeManage.h"

$PackageWebCoreBegin

template<class T, bool enabled = true>
//class IBeanInterface : public IBeanWare, public IRegisterMetaTypeUnit<T, registered>, public IRegisterTypeUnit<T, registered>
class IBeanInterface : public IBeanWare, public IStaticInitializeTaskUnit<T, enabled>
{
public:
    IBeanInterface() = default;
    virtual ~IBeanInterface() = default;

//public:
//    static void web_core_init_registerType(){
//        static std::once_flag flag;
//        std::call_once(flag, [](){

//        });
//    }

public:
    virtual void task() override{
        if(enabled){
            static std::once_flag initRegisterFlag;
            std::call_once(initRegisterFlag, [](){
                ITypeManage::registerBeanType(typeid (T).name());   // register type
                T::web_core_init_registerMetaType();                // register meta type
            });
        }
    }
};

$PackageWebCoreEnd
