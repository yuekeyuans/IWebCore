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

IStringView IQByteArrayResponseContent::getType()
{
    return CLASS_NAME;
//    static const std::string type =  "IQByteArrayResponseContent";
//    return type;
}

IStringView IQByteArrayResponseContent::getSuggestedMime()
{
    static const std::string mime = IHttpMimeUtil::toString(IHttpMime::APPLICATION_OCTET_STREAM).toStdString();
    return IStringView(mime);
}

$PackageWebCoreEnd
