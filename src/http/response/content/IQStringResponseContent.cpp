#include "IQStringResponseContent.h"
#include "http/biscuits/IHttpMime.h"

$PackageWebCoreBegin

IQStringResponseContent::IQStringResponseContent(const QString &val)
    : IResponseContentWare(val.toStdString())
{
}

IStringView IQStringResponseContent::getType()
{
    static std::string type = "IQStringResponseContent";
    return type;
}

IStringView IQStringResponseContent::getSuggestedMime()
{
    static std::string mime = IHttpMimeUtil::toString(IHttpMime::TEXT_PLAIN_UTF8).toStdString();
    return mime;
}


$PackageWebCoreEnd
