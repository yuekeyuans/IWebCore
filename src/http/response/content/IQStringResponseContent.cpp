#include "IQStringResponseContent.h"
#include "http/biscuits/IHttpMime.h"

$PackageWebCoreBegin

IQStringResponseContent::IQStringResponseContent(const QString &val)
    : IResponseContentWare(val.toStdString())
{
}

const std::string& IQStringResponseContent::getType()
{
    return CLASS_NAME;
}

const std::string& IQStringResponseContent::getSuggestedMime()
{
    static std::string mime = IHttpMimeUtil::toString(IHttpMime::TEXT_PLAIN_UTF8).toStdString();
    return mime;
}

$PackageWebCoreEnd
