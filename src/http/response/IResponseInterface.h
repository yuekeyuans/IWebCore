#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/util/IMetaUtil.h"
#include "core/unit/IRegisterMetaTypeUnit.h"
#include "http/biscuits/IHttpStatus.h"
#include "http/biscuits/IHttpMime.h"
#include "http/response/IResponseManage.h"
#include "http/response/IResponseWare.h"
#include "http/core/unit/IRegisterResponseTypeUnit.h"

$PackageWebCoreBegin

struct IResponseRaw;
class IRedirectResponse;
class IInvalidRepsonse;
class IStatusResponse;

template<typename T, bool enabled=true>
class IResponseInterface : public IResponseWare, IRegisterMetaTypeUnit<T, enabled>, IRegisterResponseTypeUnit<T, enabled>
{
public:
    IResponseInterface();
    IResponseInterface(IRedirectResponse&& response);
//    IResponseInterface(IInvalidRepsonse&& response);
    IResponseInterface(IStatusResponse&& response);
    IResponseInterface(const IResponseInterface&);
    IResponseInterface(IResponseInterface &&);
    IResponseInterface(IResponseWare*); // special // only for create
    IResponseInterface& operator=(const IResponseInterface&);
    IResponseInterface& operator=(IResponseInterface&&);
    virtual ~IResponseInterface() = default;

//public:
//    virtual IResponseWare* prefixCreate(const QString &) final;
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

template<typename T, bool enabled>
IResponseInterface<T, enabled>::IResponseInterface(IStatusResponse &&response)
{
    std::swap(this->m_raw, response.m_raw);
    this->m_raw->setMime(IHttpMime::TEXT_PLAIN_UTF8);
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
    IResponseWare::operator =(std::forward<IResponseInterface>(rhs));
    return *this;
}

//template<typename T, bool enabled>
//IResponseWare* IResponseInterface<T, enabled>::prefixCreate(const QString& val)
//{
//    return new T(val.mid(prefixMatcher().length()));
//}

$PackageWebCoreEnd
