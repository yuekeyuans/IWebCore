#include "IInvalidReponseContent.h"
#include "http/biscuits/IHttpMime.h"

$PackageWebCoreBegin

IInvalidReponseContent::IInvalidReponseContent(const IHttpInvalidWare &ware)
    : m_ware(ware) , IResponseContentWare(ware.description.toUtf8())
{
}

IStringView IInvalidReponseContent::getType()
{
    static const std::string type = "IInvalidReponseContent";
    return type;
}

IStringView IInvalidReponseContent::getSuggestedMime()
{
    static const std::string mime = IHttpMimeUtil::toString(IHttpMime::TEXT_PLAIN_UTF8).toStdString();
    return mime;
}

$PackageWebCoreEnd
