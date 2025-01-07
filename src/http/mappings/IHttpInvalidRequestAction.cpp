#include "IHttpInvalidRequestAction.h"
#include "http/net/IRequest.h"

$PackageWebCoreBegin

void IHttpInvalidRequestAction::invoke(IRequest &request) const
{
    request.doWrite();
}

$PackageWebCoreEnd
