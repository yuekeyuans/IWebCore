#include "IInvalidReponseContent.h"
#include "http/biscuits/IHttpMime.h"

$PackageWebCoreBegin

IInvalidReponseContent::IInvalidReponseContent(const IHttpInvalidWare &ware)
    : m_ware(ware) , IResponseContentWare(ware.description.toUtf8())
{
}

const std::string& IInvalidReponseContent::getType()
{
    return CLASS_NAME;
}

const std::string& IInvalidReponseContent::getSuggestedMime() const
{
    static const std::string mime = IHttpMimeUtil::toString(IHttpMime::TEXT_PLAIN_UTF8);
    return mime;
}

$PackageWebCoreEnd
