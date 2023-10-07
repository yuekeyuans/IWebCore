#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/base/IMetaUtil.h"
#include "core/bean/IBeanTypeManage.h"
#include "core/task/unit/ITaskInstantUnit.h"
#include "orm/tableview/IOrmTableWare.h"
#include "orm/tableview/IOrmTableInfo.h"

$PackageWebCoreBegin

template<typename T, bool enabled = true>
class IOrmTableInterface : public IOrmTableWare, public ITaskInstantUnit<T, enabled>
{
public:
    IOrmTableInterface() = default;
    virtual ~IOrmTableInterface() = default;

public:
    virtual QString name() const override;
    virtual QString catagory() const final;
    virtual double order() const override;
    virtual void task() override;
    virtual const IOrmTableInfo* getOrmEntityInfo() const = 0;
};

template<typename T, bool enabled>
QString IOrmTableInterface<T, enabled>::name() const
{
    return IMetaUtil::getMetaClassName(T::staticMetaObject);
}

template<typename T, bool enabled>
QString IOrmTableInterface<T, enabled>::catagory() const
{
    return "Orm";
}

template<typename T, bool enabled>
double IOrmTableInterface<T, enabled>::order() const {
    return 50;
}

template<typename T, bool enabled>
void IOrmTableInterface<T, enabled>::task(){
    if(enabled){
        static std::once_flag initRegisterFlag;
        std::call_once(initRegisterFlag, [](){
            IBeanTypeManage::registerBeanType(typeid (T).name());   // register type
            T::web_core_init_registerMetaType();                // register meta type
        });
    }
}

$PackageWebCoreEnd
