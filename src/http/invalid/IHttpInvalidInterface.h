#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/base/IMetaUtil.h"
#include "http/biscuits/IHttpStatus.h"
#include "http/invalid/IHttpInvalidWare.h"

$PackageWebCoreBegin

template<typename T>
class IHttpInvalidInterface : public IHttpInvalidWare
{
public:
    IHttpInvalidInterface(IHttpStatusCode code, const QString& description="");
};

template<typename T>
IHttpInvalidInterface<T>::IHttpInvalidInterface(IHttpStatusCode status, const QString& description)
    : IHttpInvalidWare(status, IMetaUtil::getBareTypeName<T>(), description)
{
}

$PackageWebCoreEnd
