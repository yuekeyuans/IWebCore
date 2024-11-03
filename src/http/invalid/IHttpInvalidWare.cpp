#include "IHttpInvalidWare.h"
#include "http/net/IRequest.h"
#include "http/net/IResponse.h"
#include "http/net/impl/IRequestRaw.h"
#include "http/net/impl/IResponseRaw.h"

$PackageWebCoreBegin

void IHttpInvalidWare::process(IRequest & req, IResponse &res)
{
    Q_UNUSED(req);
    auto responseRaw = res.getRaw()->m_responseRaw;
    responseRaw->status = status;
    responseRaw->setContent(responseRaw->content.contentInvalid.description);
}

$PackageWebCoreEnd
