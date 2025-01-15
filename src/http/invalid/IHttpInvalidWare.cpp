#include "IHttpInvalidWare.h"
#include "core/abort/IGlobalAbort.h"
#include "http/IRequest.h"
#include "http/IResponse.h"
#include "http/detail/IRequestRaw.h"
#include "http/detail/IResponseRaw.h"

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
