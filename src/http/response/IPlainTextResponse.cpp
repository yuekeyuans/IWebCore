#include "IPlainTextResponse.h"
#include "http/net/impl/IResponseRaw.h"
#include "http/response/content/IResponseContent.h"

$PackageWebCoreBegin

IPlainTextResponse::IPlainTextResponse()
{
    m_raw->setMime(IHttpMime::TEXT_PLAIN_UTF8);
}

IPlainTextResponse::IPlainTextResponse(const QString &value)
{
    m_raw->setContent(new IResponseContent(value.toUtf8()));
    m_raw->setMime(IHttpMime::TEXT_PLAIN_UTF8);
}

IPlainTextResponse::IPlainTextResponse(const std::string &value)
{
    m_raw->setContent(new IResponseContent(value));
    m_raw->setMime(IHttpMime::TEXT_PLAIN_UTF8);
}

IPlainTextResponse::IPlainTextResponse(const char *value)
{
    m_raw->setContent(new IResponseContent(value));
    m_raw->setMime(IHttpMime::TEXT_PLAIN_UTF8);
}

IPlainTextResponse::IPlainTextResponse(QString &&value)
{
    m_raw->setContent(new IResponseContent(value.toUtf8()));
    m_raw->setMime(IHttpMime::TEXT_PLAIN_UTF8);
}

std::string IPlainTextResponse::prefixMatcher()
{
    return "$text:";
}

IPlainTextResponse operator"" _text(const char* str, size_t size)
{
    return QString::fromLocal8Bit(str, static_cast<int>(size));
}


$PackageWebCoreEnd
