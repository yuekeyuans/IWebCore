#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/util/IMetaUtil.h"
#include "http/IHttpManage.h"
#include "http/biscuits/IHttpStatus.h"
#include "http/invalid/IHttpInvalidWare.h"
#include "http/invalid/IHttpInvalidHandlerInterface.h"
#include "core/unit/IClassNameUnit.h"
#include <functional>

$PackageWebCoreBegin

template<typename T, bool enabled=true>
class IHttpInvalidInterface : public IHttpInvalidWare, public IClassNameUnit<T>
{
public:
    IHttpInvalidInterface(IHttpStatus code);
    IHttpInvalidInterface(IHttpStatus code, const QString& description);
};

template<typename T, bool enabled>
IHttpInvalidInterface<T, enabled>::IHttpInvalidInterface(IHttpStatus status)
    : IHttpInvalidWare(status, IMetaUtil::getBareTypeName<T>())
{
    static std::function<void(const IHttpInvalidWare&, IResponseRaw&)> s_funs {nullptr};
    static std::once_flag flag;
    std::call_once(flag, [](){
        if constexpr(&T::process != &IHttpInvalidWare::process){
            s_funs  = [](const IHttpInvalidWare& ware, IResponseRaw& respRaw){
                ISingletonUnitDetail::getInstance<T>()->T::process(ware, respRaw);
            };
        }else{
            auto handler = IHttpManage::instance()->getInvalidHandler(T::CLASS_NAME);
            if(handler){
                s_funs = [=](const IHttpInvalidWare& ware, IResponseRaw& respRaw){
                    handler->handle(ware, respRaw);
                };
            }
        }
    });

    m_function = s_funs;
}

template<typename T, bool enabled>
IHttpInvalidInterface<T, enabled>::IHttpInvalidInterface(IHttpStatus status, const QString& description)
    : IHttpInvalidWare(status, description)
{
    if constexpr(&T::process != &IHttpInvalidWare::process){
        m_function  = [](const IHttpInvalidWare& ware, IResponseRaw& respRaw){
            ISingletonUnitDetail::getInstance<T>()->process(ware, respRaw);
        };
    }
}

$PackageWebCoreEnd
