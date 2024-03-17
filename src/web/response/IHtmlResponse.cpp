#include "IHtmlResponse.h"
#include "core/base/IMetaUtil.h"

$PackageWebCoreBegin

IHtmlResponse::IHtmlResponse() : IResponseInterface()
{
    raw->setMime(IHttpMime::TEXT_HTML_UTF8);
}

IHtmlResponse::IHtmlResponse(const char *data)
{
    raw->setMime(IHttpMime::TEXT_HTML_UTF8);
    raw->setContent(data);
}

IHtmlResponse::IHtmlResponse(const QString &data)
{
    raw->setMime(IHttpMime::TEXT_HTML_UTF8);
    raw->setContent(data);
}

QString IHtmlResponse::getPrefixMatcher()
{
    return "$html:";
}

IHtmlResponse operator"" _html(const char* str, size_t size)
{
    QByteArray array(str, static_cast<int>(size));
    IHtmlResponse response;
    response.setContent(array);
    return response;
}

$PackageWebCoreEnd
