#include "IPlainTextResponse.h"
#include "IResponseWareRaw.h"

$PackageWebCoreBegin

IPlainTextResponse::IPlainTextResponse()
{
    raw->setMime(IHttpMime::TEXT_PLAIN_UTF8);
}

IPlainTextResponse::IPlainTextResponse(const QString &value)
{
    raw->setContent(value);
    raw->setMime(IHttpMime::TEXT_PLAIN_UTF8);
}

IPlainTextResponse::IPlainTextResponse(QString &&value)
{
    raw->setContent(value);
    raw->setMime(IHttpMime::TEXT_PLAIN_UTF8);
}

IPlainTextResponse::IPlainTextResponse(const char *data)
{
    raw->setContent(QByteArray(data));
    raw->setMime(IHttpMime::TEXT_PLAIN_UTF8);
}

QString IPlainTextResponse::getPrefixMatcher()
{
    return "$text:";
}

IPlainTextResponse operator"" _text(const char* str, size_t size)
{
    return QString::fromLocal8Bit(str, static_cast<int>(size));
}


$PackageWebCoreEnd
