#pragma once

#include "base/IHeaderUtil.h"
#include "bean/IBeanInterface.h"
#include "orm/tableview/IOrmTableWare.h"

$PackageWebCoreBegin

template<typename T, bool enabled = true>
class IOrmTableInterface : public IOrmTableWare,  public IRegisterMetaTypeUnit<T, enabled>, public IRegisterTypeUnit<T, enabled>
{
public:
    IOrmTableInterface() = default;
    virtual ~IOrmTableInterface() = default;

public:
    static void web_core_init_registerType(){
        static std::once_flag flag;
        std::call_once(flag, [](){
            ITypeManage::registerBeanType(typeid (T).name());
        });
    }
};

$PackageWebCoreEnd
