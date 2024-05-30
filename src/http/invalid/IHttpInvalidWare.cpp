#include "IHttpInvalidWare.h"
#include "http/net/IRequest.h"
#include "http/net/IResponse.h"
#include "http/net/impl/IRequestRaw.h"
#include "http/net/impl/IResponseRaw.h"

$PackageWebCoreBegin

void IHttpInvalidWare::process(IRequest & req, IResponse &res)
{
    Q_UNUSED(req);
    auto content = res.getRaw()->m_responseRaw;
    content->status = status;
    content->setContent(content->content.contentInvalid.description);
}

$PackageWebCoreEnd
