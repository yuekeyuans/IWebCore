#include "IInvalidResponse.h"
#include "core/abort/IGlobalAbort.h"
#include "http/net/impl/IResponseRaw.h"

$PackageWebCoreBegin

IInvalidResponse::IInvalidResponse(const QString &value)
{
    Q_UNUSED(value)
    IGlobalAbort::abortUnVisibleMethod();
}

IInvalidResponse::IInvalidResponse(IHttpInvalidWare ware)
{
    m_raw->setMime(IHttpMime::TEXT_PLAIN_UTF8);
    m_raw->setContent(ware);
}

$PackageWebCoreEnd
