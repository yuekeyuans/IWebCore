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

$PackageWebCoreEnd
