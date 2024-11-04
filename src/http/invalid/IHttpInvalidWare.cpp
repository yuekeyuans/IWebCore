#include "IHttpInvalidWare.h"
#include "http/net/IRequest.h"
#include "http/net/IResponse.h"
#include "http/net/impl/IRequestRaw.h"
#include "http/net/impl/IResponseRaw.h"

$PackageWebCoreBegin

IHttpInvalidWare::IHttpInvalidWare(IHttpStatusCode code, QString description)
    : status(code), description(std::move(description))
{
}

void IHttpInvalidWare::process(IRequest&, IResponse&)
{
//    Q_UNUSED(req);
//    auto responseRaw = res.getRaw()->m_responseRaw;
//    responseRaw->status = status;
    //    responseRaw->setContent(responseRaw->content.contentInvalid.description);
}

$PackageWebCoreEnd
