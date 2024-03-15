#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/base/IMetaUtil.h"
#include "core/unit/IRegisterMetaTypeUnit.h"
#include "web/biscuits/IHttpStatus.h"
#include "web/biscuits/IHttpMime.h"
#include "web/response/IResponseManage.h"
#include "web/response/IResponseWare.h"
#include "web/core/unit/IRegisterResponseTypeUnit.h"

$PackageWebCoreBegin

struct IResponseWareRaw;
class IRedirectResponse;

template<typename T>
class IResponseInterface : public IResponseWare, IRegisterMetaTypeUnit<T>, IRegisterResponseTypeUnit<T>
{
public:
    using IResponseWare::operator[];

public:
    IResponseInterface() = default;
    IResponseInterface(IRedirectResponse&& response);
    virtual ~IResponseInterface() = default;
};

template<typename T>
IResponseInterface<T>::IResponseInterface(IRedirectResponse &&response)
{
    redirectTo(std::forward<IRedirectResponse>(response));
}

$PackageWebCoreEnd
