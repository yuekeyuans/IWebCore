﻿#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/util/IMetaUtil.h"
#include "core/task/ITaskPreProcessor.h"

$PackageWebCoreBegin

template<typename T, bool enabled = true>
class IRegisterMetaTypeUnit
{
    $AsTaskUnit(IRegisterMetaTypeUnit)
protected:
    IRegisterMetaTypeUnit() = default;
    virtual ~IRegisterMetaTypeUnit() = default;
};

$UseTaskUnit(IRegisterMetaTypeUnit)
{
    if(enabled){
        static std::once_flag initRegisterFlag;
        std::call_once(initRegisterFlag, [](){
            IMetaUtil::registerMetaType<T>();
        });
    }
}

$PackageWebCoreEnd
