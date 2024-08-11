﻿#pragma once

#include "IBeanWare.h"
#include "IBeanTypeManage.h"
#include "core/util/IHeaderUtil.h"
#include "core/util/IMetaUtil.h"
#include "core/unit/ITraceUnit.h"
#include "core/bean/IBeanPreProcessor.h"
#include "core/task/unit/ITaskInstantUnit.h"

$PackageWebCoreBegin

template<class T, bool enabled = true>
class IBeanInterface : public IBeanWare, public ITaskInstantUnit<T, enabled>, public ITraceUnit<T, false>
{
public:
    IBeanInterface() = default;
    virtual ~IBeanInterface() = default;

public:
    virtual QString name() const;
    virtual void task() final;
};

template <typename T, bool enabled>
QString IBeanInterface<T, enabled>::name() const
{
    return IMetaUtil::getTypename<T>();
}

template<typename T, bool enabled>
void IBeanInterface<T, enabled>::task()
{
    if(enabled){
        static std::once_flag initRegisterFlag;
        std::call_once(initRegisterFlag, [](){
            IBeanTypeManage::registerBeanType(typeid (T).name());   // register type
            IMetaUtil::registerMetaType<T>();
        });
    }
}

$PackageWebCoreEnd
