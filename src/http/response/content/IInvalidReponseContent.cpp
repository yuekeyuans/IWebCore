#include "IInvalidReponseContent.h"
#include "http/biscuits/IHttpMime.h"
#include "http/net/impl/IResponseRaw.h"

$PackageWebCoreBegin

IInvalidReponseContent::IInvalidReponseContent(const IHttpInvalidWare &ware)
    :IResponseContent(ware.description)
{
    if(ware.m_function){
        m_function = [=](IResponseRaw& raw){
            ware.m_function(ware, raw);
        };
    }
}

$PackageWebCoreEnd
