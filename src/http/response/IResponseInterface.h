#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/util/IMetaUtil.h"
#include "core/unit/IRegisterMetaTypeUnit.h"
#include "http/biscuits/IHttpStatus.h"
#include "http/biscuits/IHttpMime.h"
#include "http/response/IRegisterResponseUnit.h"
#include "http/response/IResponseManage.h"
#include "http/response/IResponseWare.h"
#include "http/response/content/IInvalidReponseContent.h"
#include "http/invalid/IHttpInvalidWare.h"

$PackageWebCoreBegin

namespace detail
{
    template<typename T, bool enabled>
    class IRegisterResponseUnit
    {
        $AsTaskUnit(IRegisterResponseUnit)
    public:
        IRegisterResponseUnit() = default;
    };

    $UseTaskUnit(IRegisterResponseUnit)
    {
        static std::once_flag flag;
        std::call_once(flag, [](){
            IResponseManage::instance()->registerResponse(IMetaUtil::getBareTypeName<T>(),
                                                          ISingletonUnitDetail::getInstance<T>());
        });
    }
}

class IResponseRaw;
class IRedirectResponse;
class IStatusResponse;
template<typename T, bool enabled=true>
class IResponseInterface : public IResponseWare, IRegisterMetaTypeUnit<T, enabled>, detail::IRegisterResponseUnit<T, enabled>
{
public:
    IResponseInterface() = default;
    virtual ~IResponseInterface() = default;

    IResponseInterface(IRedirectResponse&& response);
    IResponseInterface(const IRedirectResponse&){}

    IResponseInterface(const IHttpInvalidWare&);

    IResponseInterface(IStatusResponse&& response);
    IResponseInterface(const IStatusResponse&){}

    IResponseInterface(IResponseInterface &&);
    IResponseInterface(const IResponseInterface&);
    IResponseInterface& operator=(const IResponseInterface&);
    IResponseInterface& operator=(IResponseInterface&&);
};

template<typename T, bool enabled>
IResponseInterface<T, enabled>::IResponseInterface(IRedirectResponse &&response)
{
    std::swap(this->m_raw, response.m_raw);
}

template<typename T, bool enabled>
IResponseInterface<T, enabled>::IResponseInterface(const IHttpInvalidWare& ware)
{ 
    this->m_raw->m_status = ware.status;
    this->m_raw->setContent(ware);
}

template<typename T, bool enabled>
IResponseInterface<T, enabled>::IResponseInterface(IStatusResponse &&response)
{
    std::swap(this->m_raw, response.m_raw);
}

template<typename T, bool enabled>
IResponseInterface<T, enabled>::IResponseInterface(const IResponseInterface &rhs)
    : IResponseWare(rhs)
{
}

template<typename T, bool enabled>
IResponseInterface<T, enabled>::IResponseInterface(IResponseInterface &&rhs)
    : IResponseWare(std::forward<IResponseInterface>(rhs))
{
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
