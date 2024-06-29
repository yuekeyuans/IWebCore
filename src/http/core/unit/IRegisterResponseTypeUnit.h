#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/task/ITaskPreProcessor.h"

$PackageWebCoreBegin

template<typename T, bool enabled>
class IRegisterResponseTypeUnit
{
    $AsTaskUnit(IRegisterResponseTypeUnit)
public:
    IRegisterResponseTypeUnit() = default;
};

$UseTaskUnit(IRegisterResponseTypeUnit)
{
    static std::once_flag flag;
    std::call_once(flag, [](){
        static T t;
        IResponseManage::instance()->registerResponseType(&t);
    });
}

$PackageWebCoreEnd
