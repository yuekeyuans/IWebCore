#include "IHttpInvalidWare.h"
#include "http/net/IRequest.h"
#include "http/net/IResponse.h"
#include "http/net/impl/IReqRespRaw.h"

$PackageWebCoreBegin

void IHttpInvalidWare::process(IRequest & req, IResponse &res)
{
    Q_UNUSED(req);
    auto& content = res.getRaw()->m_responseContent;
    content.setContent(content.contentInvalid.description);
}

$PackageWebCoreEnd
