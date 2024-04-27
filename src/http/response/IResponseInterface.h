#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/base/IMetaUtil.h"
#include "core/unit/IRegisterMetaTypeUnit.h"
#include "http/biscuits/IHttpStatus.h"
#include "http/biscuits/IHttpMime.h"
#include "http/response/IResponseManage.h"
#include "http/response/IResponseWare.h"
#include "http/response/IResponseWareRaw.h"
#include "http/core/unit/IRegisterResponseTypeUnit.h"

$PackageWebCoreBegin

struct IResponseWareRaw;
class IRedirectResponse;
class IInvalidRepsonse;
class IStatusResponse;

template<typename T>
class IResponseInterface : public IResponseWare, IRegisterMetaTypeUnit<T>, IRegisterResponseTypeUnit<T>
{
public:
    using IResponseWare::operator[];

public:
    IResponseInterface();
    IResponseInterface(IRedirectResponse&& response);
    IResponseInterface(IInvalidRepsonse&& response);
    IResponseInterface(IStatusResponse&& response);
    IResponseInterface(const IResponseInterface&);
    IResponseInterface(IResponseInterface &&);
    IResponseInterface(IResponseWare*); // special // only for create
    IResponseInterface& operator=(const IResponseInterface&);
    IResponseInterface& operator=(IResponseInterface&&);

    virtual ~IResponseInterface() = default;

public:
    virtual QSharedPointer<IResponseWare> create(IResponseWare*) override;
    virtual QSharedPointer<IResponseWare> create(QString val) final;
};

template<typename T>
IResponseInterface<T>::IResponseInterface()
{
}

template<typename T>
IResponseInterface<T>::IResponseInterface(IRedirectResponse &&response)
{
    response.updateLocationPath();
    std::swap(this->m_raw, response.m_raw);
//    redirectTo(std::forward<IRedirectResponse>(response));
}

template<typename T>
IResponseInterface<T>::IResponseInterface(IInvalidRepsonse &&response)
{
    std::swap(this->m_raw, response.m_raw);
}

template<typename T>
IResponseInterface<T>::IResponseInterface(IStatusResponse &&response)
{
    std::swap(this->m_raw, response.m_raw);
    this->m_raw->setMime(IHttpMime::TEXT_PLAIN_UTF8);
}

template<typename T>
IResponseInterface<T>::IResponseInterface(const IResponseInterface &rhs) : IResponseWare(rhs)
{
}

template<typename T>
IResponseInterface<T>::IResponseInterface(IResponseInterface &&rhs) : IResponseWare(std::forward<IResponseInterface>(rhs))
{
}

template<typename T>
IResponseInterface<T>::IResponseInterface(IResponseWare *ware)
{
    std::swap(this->m_raw, ware->m_raw);
}

template<typename T>
IResponseInterface<T> &IResponseInterface<T>::operator=(const IResponseInterface&rhs)
{
    IResponseWare::operator =(rhs);
    return *this;
}

template<typename T>
IResponseInterface<T> &IResponseInterface<T>::operator=(IResponseInterface &&rhs)
{
    IResponseWare::operator =(std::forward<IResponseInterface>(rhs));
    return *this;
}

template<typename T>
QSharedPointer<IResponseWare> IResponseInterface<T>::create(IResponseWare *ware)
{
    return QSharedPointer<T>::create(ware);
}

template<typename T>
QSharedPointer<IResponseWare> IResponseInterface<T>::create(QString val)
{
    return QSharedPointer<T>::create(val.mid(getPrefixMatcher().length())); // TODO: 倒也不必每次调用， 这里之后静态初始化这个值。
}

$PackageWebCoreEnd
