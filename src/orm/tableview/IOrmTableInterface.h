#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/util/IMetaUtil.h"
#include "core/bean/IBeanTypeManage.h"
#include "core/task/unit/ITaskInstantUnit.h"
#include "orm/tableview/IOrmTableWare.h"
#include "orm/tableview/IOrmTableInfo.h"

$PackageWebCoreBegin

// TODO: check ITaskInstantUnit
template<typename T, bool enabled = true>
class IOrmTableInterface : public IOrmTableWare, public ITaskInstantUnit<T, enabled>
{
public:
    IOrmTableInterface() = default;
    virtual ~IOrmTableInterface() = default;

public:
//    virtual QString $name() const override;
//    virtual const QString& $catagory() const final;
    virtual void $task() override;
    virtual const IOrmTableInfo* getOrmEntityInfo() const = 0;
};

//template<typename T, bool enabled>
//QString IOrmTableInterface<T, enabled>::$name() const
//{
//    return IMetaUtil::getMetaClassName(T::staticMetaObject);
//}

//template<typename T, bool enabled>
//QString IOrmTableInterface<T, enabled>::$catagory() const
//{
//    return "Orm";
//}

// TODO: view detail whether this is right?
template<typename T, bool enabled>
void IOrmTableInterface<T, enabled>::task(){
    if constexpr (enabled){
        static std::once_flag initRegisterFlag;
        std::call_once(initRegisterFlag, [](){
            IBeanTypeManage::registerBeanType(typeid (T).name());   // register type
//            T::web_core_init_registerMetaType();                // register meta type
        });
    }
}

$PackageWebCoreEnd
