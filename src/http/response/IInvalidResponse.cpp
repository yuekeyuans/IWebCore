#include "IInvalidResponse.h"

$PackageWebCoreBegin

IInvalidResponse::IInvalidResponse(const QString &value)
{

}

IInvalidResponse::IInvalidResponse(IHttpInvalidWare ware)
{
    m_raw->setMime(IHttpMime::TEXT_PLAIN_UTF8);
    m_raw->setContent(ware);
}

$PackageWebCoreEnd
