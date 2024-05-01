#include "IHttpInvalidWare.h"
#include "http/net/IRequest.h"
#include "http/net/IResponse.h"
#include "http/net/impl/IReqRespRaw.h"
#include "http/net/impl/IResponseRaw.h"

$PackageWebCoreBegin

void IHttpInvalidWare::process(IRequest & req, IResponse &res)
{
    Q_UNUSED(req);
    auto content = res.getRaw()->m_responseRaw;
    content->setContent(content->content.contentInvalid.description);
}

$PackageWebCoreEnd
