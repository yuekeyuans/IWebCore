#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/util/IMetaUtil.h"
#include "core/unit/IRegisterMetaTypeUnit.h"
#include "http/biscuits/IHttpStatus.h"
#include "http/biscuits/IHttpMime.h"
#include "http/response/IResponseManage.h"
#include "http/response/IResponseWare.h"
#include "http/core/unit/IRegisterResponseTypeUnit.h"
#include "http/invalid/IHttpInvalidWare.h"

$PackageWebCoreBegin

struct IResponseRaw;
class IRedirectResponse;
class IStatusResponse;

template<typename T, bool enabled=true>
class IResponseInterface : public IResponseWare, IRegisterMetaTypeUnit<T, enabled>, IRegisterResponseTypeUnit<T, enabled>
{
public:
    IResponseInterface();
    IResponseInterface(IRedirectResponse&& response);
    IResponseInterface(const IRedirectResponse&){}

    IResponseInterface(IHttpInvalidWare);

    IResponseInterface(IStatusResponse&& response);
    IResponseInterface(const IStatusResponse&){}

    IResponseInterface(IResponseInterface &&);
    IResponseInterface(const IResponseInterface&);

    IResponseInterface(IResponseWare*); // special // only for create
    IResponseInterface& operator=(const IResponseInterface&);
    IResponseInterface& operator=(IResponseInterface&&);
    virtual ~IResponseInterface() = default;

};

template<typename T, bool enabled>
IResponseInterface<T, enabled>::IResponseInterface()
{
}

template<typename T, bool enabled>
IResponseInterface<T, enabled>::IResponseInterface(IRedirectResponse &&response)
{
    response.updateLocationPath();
    std::swap(this->m_raw, response.m_raw);
}

//template<typename T, bool enabled>
//IResponseInterface<T, enabled>::IResponseInterface(IInvalidRepsonse &&response)
//{
//    std::swap(this->m_raw, response.m_raw);
//}

#include "http/response/content/IInvalidReponseContent.h"
#include "http/response/IInvalidResponse.h"

template<typename T, bool enabled>
IResponseInterface<T, enabled>::IResponseInterface(IHttpInvalidWare ware)
{
    IInvalidResponse resp(ware);
    std::swap(this->m_raw, resp.m_raw);
}

template<typename T, bool enabled>
IResponseInterface<T, enabled>::IResponseInterface(IStatusResponse &&response)
{
    std::swap(this->m_raw, response.m_raw);
}

template<typename T, bool enabled>
IResponseInterface<T, enabled>::IResponseInterface(const IResponseInterface &rhs) : IResponseWare(rhs)
{
}

template<typename T, bool enabled>
IResponseInterface<T, enabled>::IResponseInterface(IResponseInterface &&rhs) : IResponseWare(std::forward<IResponseInterface>(rhs))
{
}

template<typename T, bool enabled>
IResponseInterface<T, enabled>::IResponseInterface(IResponseWare *ware)
{
    std::swap(this->m_raw, ware->m_raw);
}

template<typename T, bool enabled>
IResponseInterface<T, enabled> &IResponseInterface<T, enabled>::operator=(const IResponseInterface&rhs)
{
    IResponseWare::operator =(rhs);
    return *this;
}

template<typename T, bool enabled>
IResponseInterface<T, enabled> &IResponseInterface<T, enabled>::operator=(IResponseInterface &&rhs)
{
    IResponseWare::operator =(std::move(rhs));
    return *this;
}

$PackageWebCoreEnd
