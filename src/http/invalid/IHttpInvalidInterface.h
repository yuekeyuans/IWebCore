#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/util/IMetaUtil.h"
#include "http/biscuits/IHttpStatus.h"
#include "http/invalid/IHttpInvalidWare.h"

$PackageWebCoreBegin

template<typename T, bool enabled=true>
class IHttpInvalidInterface : public IHttpInvalidWare
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
        m_function = std::mem_fun(&T::process, this);
    }
}

template<typename T, bool enabled>
IHttpInvalidInterface<T, enabled>::IHttpInvalidInterface(IHttpStatusCode status, const QString& description)
    : IHttpInvalidWare(status, description)
{
    if constexpr(&T::process != &IHttpInvalidWare::process){
        m_function = std::mem_fun(&T::process, this);
    }
}

$PackageWebCoreEnd
