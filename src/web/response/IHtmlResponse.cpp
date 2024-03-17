#include "IHtmlResponse.h"
#include "core/base/IMetaUtil.h"

$PackageWebCoreBegin

IHtmlResponse::IHtmlResponse() : IResponseInterface()
{
    m_raw->setMime(IHttpMime::TEXT_HTML_UTF8);
}

IHtmlResponse::IHtmlResponse(const char *data)
{
    m_raw->setMime(IHttpMime::TEXT_HTML_UTF8);
    m_raw->setContent(data);
}

IHtmlResponse::IHtmlResponse(const QString &data)
{
    m_raw->setMime(IHttpMime::TEXT_HTML_UTF8);
    m_raw->setContent(data);
}

QString IHtmlResponse::getPrefixMatcher()
{
    return "$html:";
}

IHtmlResponse operator"" _html(const char* str, size_t size)
{
    Q_UNUSED(size)
    return IHtmlResponse(str);
}

$PackageWebCoreEnd
