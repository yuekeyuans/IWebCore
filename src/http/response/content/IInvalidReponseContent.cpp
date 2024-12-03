#include "IInvalidReponseContent.h"
#include "http/biscuits/IHttpMime.h"

$PackageWebCoreBegin

IInvalidReponseContent::IInvalidReponseContent(const IHttpInvalidWare &ware)
    : m_ware(ware) , IResponseContent(ware.description)
{
}

$PackageWebCoreEnd
