#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/task/ITaskPreProcessor.h"

#include <mutex>

$PackageWebCoreBegin

template<typename T, bool enabled>
class IRegistInvalidUnit
{
    $AsTaskUnit(IRegistInvalidUnit)
public:
    IRegistInvalidUnit() = default;
};

$UseTaskUnit(IRegistInvalidUnit)
{
    static std::once_flag flag;
    if(enabled){
        std::call_once(flag, [](){
           qDebug() << "run herer";
        });
    }
}

$PackageWebCoreEnd
