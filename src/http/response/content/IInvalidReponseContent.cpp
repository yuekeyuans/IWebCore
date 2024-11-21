#include "IInvalidReponseContent.h"
#include "http/biscuits/IHttpMime.h"

$PackageWebCoreBegin

IInvalidReponseContent::IInvalidReponseContent(IHttpInvalidWare &ware)
    : m_ware(ware)
{
}

int IInvalidReponseContent::getSize()
{
    return {};
}

const char *IInvalidReponseContent::getType()
{
    return "invalidware";
}

IStringView IInvalidReponseContent::getContent()
{
    return {};
}

QString IInvalidReponseContent::getSuggestedMime()
{
    return IHttpMimeUtil::toString(IHttpMime::TEXT_PLAIN_UTF8);
}


$PackageWebCoreEnd
