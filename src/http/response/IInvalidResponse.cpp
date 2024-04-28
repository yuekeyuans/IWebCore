#include "IInvalidResponse.h"

$PackageWebCoreBegin

IInvalidResponse::IInvalidResponse(const QString &value)
{
    Q_UNUSED(value)
    qFatal(IConstantUtil::UnCallableMethod);
}

IInvalidResponse::IInvalidResponse(IHttpInvalidUnit ware)
{
    m_raw->setMime(IHttpMime::TEXT_PLAIN_UTF8);
    m_raw->setContent(ware);
}

$PackageWebCoreEnd
