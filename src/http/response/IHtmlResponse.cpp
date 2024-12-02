#include "IHtmlResponse.h"
#include "core/util/IMetaUtil.h"
#include "http/response/content/IStringResponseContent.h"

$PackageWebCoreBegin

IHtmlResponse::IHtmlResponse() : IResponseInterface()
{
    m_raw->setMime(IHttpMime::TEXT_HTML_UTF8);
}

IHtmlResponse::IHtmlResponse(const QString &data)
{
    m_raw->setMime(IHttpMime::TEXT_HTML_UTF8);
    m_raw->setContent(new IStringResponseContent(data.toUtf8()));
}

IHtmlResponse::IHtmlResponse(std::string && data)
{
    m_raw->setMime(IHttpMime::TEXT_HTML_UTF8);
    m_raw->setContent(new IStringResponseContent(std::move(data)));
}

IHtmlResponse::IHtmlResponse(const std::string & data)
{
    m_raw->setMime(IHttpMime::TEXT_HTML_UTF8);
    m_raw->setContent(new IStringResponseContent(data));
}

IHtmlResponse::IHtmlResponse(QByteArray &&data)
{
    m_raw->setMime(IHttpMime::TEXT_HTML_UTF8);
    m_raw->setContent(new IStringResponseContent(std::move(data)));
}

IHtmlResponse::IHtmlResponse(const QByteArray &data)
{
    m_raw->setMime(IHttpMime::TEXT_HTML_UTF8);
    m_raw->setContent(new IStringResponseContent(data));
}

std::string IHtmlResponse::prefixMatcher()
{
    return "$html:";
}

IHtmlResponse operator"" _html(const char* str, size_t size)
{
    return IHtmlResponse(std::string(str, size));
}

$PackageWebCoreEnd
