#include "IQByteArrayResponseContent.h"
#include "http/biscuits/IHttpMime.h"

$PackageWebCoreBegin

IQByteArrayResponseContent::IQByteArrayResponseContent(QByteArray && val)
    : IResponseContentWare(std::move(val))
{
}

IQByteArrayResponseContent::IQByteArrayResponseContent(const QByteArray & val)
    : IResponseContentWare(val)
{
}

const std::string& IQByteArrayResponseContent::getType()
{
    return CLASS_NAME;
}

const std::string& IQByteArrayResponseContent::getSuggestedMime() const
{
    static const std::string& mime = IHttpMimeUtil::toString(IHttpMime::APPLICATION_OCTET_STREAM);
    return mime;
}

$PackageWebCoreEnd
