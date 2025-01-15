#include "IInvalidReponseContent.h"
#include "core/util/IConstantUtil.h"
#include "http/biscuits/IHttpMime.h"
#include "http/detail/IResponseRaw.h"

$PackageWebCoreBegin

IInvalidReponseContent::IInvalidReponseContent(const IHttpInvalidWare &ware)
    :IResponseContent(ware.description)
{
    setAttribute(&IConstantUtil::Type, &IInvalidReponseContent::Type);

    if(ware.m_function){
        m_function = [=](const IResponseContent&, IResponseRaw& raw){
            ware.m_function(ware, raw);
        };
    }
}

$PackageWebCoreEnd
