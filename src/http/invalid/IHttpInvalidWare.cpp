#include "IHttpInvalidWare.h"
#include "core/abort/IGlobalAbort.h"
#include "http/net/IRequest.h"
#include "http/net/IResponse.h"
#include "http/net/impl/IRequestRaw.h"
#include "http/net/impl/IResponseRaw.h"

$PackageWebCoreBegin

IHttpInvalidWare::IHttpInvalidWare(IHttpStatusCode code, QString description)
    : status(code), description(std::move(description))
{
}

void IHttpInvalidWare::process(IRequest&)
{
    IGlobalAbort::abortUnReachableCode($ISourceLocation);
}

$PackageWebCoreEnd
