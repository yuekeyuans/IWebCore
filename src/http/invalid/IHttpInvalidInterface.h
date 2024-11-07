#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/util/IMetaUtil.h"
#include "http/biscuits/IHttpStatus.h"
#include "http/invalid/IHttpInvalidWare.h"
#include "core/unit/IClassNameUnit.h"
#include <functional>

$PackageWebCoreBegin

template<typename T, bool enabled=true>
class IHttpInvalidInterface : public IHttpInvalidWare, public IClassNameUnit<T>
{
public:
    IHttpInvalidInterface(IHttpStatusCode code);
    IHttpInvalidInterface(IHttpStatusCode code, const QString& description);
};

template<typename T, bool enabled>
IHttpInvalidInterface<T, enabled>::IHttpInvalidInterface(IHttpStatusCode status)
    : IHttpInvalidWare(status, IMetaUtil::getBareTypeName<T>())
{
    if constexpr(&T::process != &IHttpInvalidWare::process){
        m_function  = [](IRequest& request){
            ISingletonUnitDetail::getInstance<T>()->T::process(request);
        };
    }
}

template<typename T, bool enabled>
IHttpInvalidInterface<T, enabled>::IHttpInvalidInterface(IHttpStatusCode status, const QString& description)
    : IHttpInvalidWare(status, description)
{
    if constexpr(&T::process != &IHttpInvalidWare::process){
        m_function  = [](IRequest& request){
            ISingletonUnitDetail::getInstance<T>()->process(request);
        };
    }
}

$PackageWebCoreEnd
