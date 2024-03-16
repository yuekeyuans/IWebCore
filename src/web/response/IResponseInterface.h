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
    IResponseInterface();
    IResponseInterface(IRedirectResponse&& response);
    IResponseInterface(const IResponseInterface&);
    IResponseInterface(IResponseInterface &&);
    IResponseInterface& operator=(const IResponseInterface&);
    IResponseInterface& operator=(IResponseInterface&&);

    virtual ~IResponseInterface() = default;
};


template<typename T>
IResponseInterface<T>::IResponseInterface()
{
    qDebug() << "construct";
}

template<typename T>
IResponseInterface<T>::IResponseInterface(IRedirectResponse &&response)
{
    redirectTo(std::forward<IRedirectResponse>(response));
}

template<typename T>
IResponseInterface<T>::IResponseInterface(const IResponseInterface &rhs) : IResponseWare(rhs)
{
    qDebug() << "copy construct";
}

template<typename T>
IResponseInterface<T>::IResponseInterface(IResponseInterface &&rhs) : IResponseWare(std::forward<IResponseInterface>(rhs))
{
    qDebug() << "move construct";
}

template<typename T>
IResponseInterface<T> &IResponseInterface<T>::operator=(const IResponseInterface&rhs)
{
    qDebug() << "assign const";
    this->operator =(rhs);
    return *this;
}

template<typename T>
IResponseInterface<T> &IResponseInterface<T>::operator=(IResponseInterface &&rhs)
{
    qDebug() << "assign move";
    this->operator =(std::forward<IResponseInterface>(rhs));
    return *this;
}

$PackageWebCoreEnd
