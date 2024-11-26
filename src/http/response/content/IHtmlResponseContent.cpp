#include "IHtmlResponseContent.h"
#include "http/biscuits/IHttpMime.h"

$PackageWebCoreBegin

IHtmlResponseContent::IHtmlResponseContent(QByteArray && value)
    : IResponseContentWare(std::move(value))
{
}

IHtmlResponseContent::IHtmlResponseContent(const QByteArray &value)
    : IResponseContentWare(value)
{
}

IHtmlResponseContent::IHtmlResponseContent(std::string &&value)
    : IResponseContentWare(std::move(value))
{
}

IHtmlResponseContent::IHtmlResponseContent(const std::string &value)
    : IResponseContentWare(value)
{
}

IHtmlResponseContent::IHtmlResponseContent(const QString &value)
    : IResponseContentWare(value.toStdString())
{
}

IHtmlResponseContent::IHtmlResponseContent(IStringView view)
    :IResponseContentWare(view)
{
}

const std::string &IHtmlResponseContent::getType()
{
    return CLASS_NAME;
}

const std::string& IHtmlResponseContent::getSuggestedMime() const
{
    static auto mime = IHttpMimeUtil::toString(IHttpMime::TEXT_HTML_UTF8);
    return mime;
}

$PackageWebCoreEnd
