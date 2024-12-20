#include "IHttpInvalidWare.h"
#include "core/abort/IGlobalAbort.h"
#include "http/net/IRequest.h"
#include "http/net/IResponse.h"
#include "http/net/impl/IRequestRaw.h"
#include "http/net/impl/IResponseRaw.h"

$PackageWebCoreBegin

IHttpInvalidWare::IHttpInvalidWare(IHttpStatus code)
    : status(code), description(IHttpStatusUtil::toStringDescription(code).toStdString())
{
}

IHttpInvalidWare::IHttpInvalidWare(IHttpStatus code, const std::string& description)
    : status(code), description(description)
{
}

void IHttpInvalidWare::process(const IHttpInvalidWare&, IResponseRaw&)
{
    IGlobalAbort::abortUnReachableCode($ISourceLocation);
}

$PackageWebCoreEnd
