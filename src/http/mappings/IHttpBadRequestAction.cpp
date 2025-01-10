#include "IHttpBadRequestAction.h"
#include "http/invalid/IHttpBadRequestInvalid.h"
#include "http/net/IRequest.h"

$PackageWebCoreBegin

void IHttpBadRequestAction::invoke(IRequest &request) const
{
    request.setInvalid(IHttpBadRequestInvalid());
    request.doWrite();
}

$PackageWebCoreEnd
