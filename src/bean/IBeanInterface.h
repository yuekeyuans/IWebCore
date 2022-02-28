#pragma once

#include "base/IHeaderUtil.h"
#include "bean/IBeanWare.h"
#include "common/support/IRegisterMetaTypeUnit.h"
#include "common/support/IRegisterTypeUnit.h"
#include "common/type/ITypeManage.h"

$PackageWebCoreBegin

template<class T, bool registered = true>
class IBeanInterface : public IBeanWare, public IRegisterMetaTypeUnit<T, registered>, public IRegisterTypeUnit<T, registered>
{
public:
    IBeanInterface() = default;
    virtual ~IBeanInterface() = default;

public:
    static void web_core_init_registerType(){
        static std::once_flag flag;
        std::call_once(flag, [](){
            ITypeManage::registerBeanType(typeid (T).name());
        });
    }
};

$PackageWebCoreEnd
