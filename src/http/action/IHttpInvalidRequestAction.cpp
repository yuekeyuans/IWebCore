#include "IHttpInvalidRequestAction.h"
#include "http/IRequest.h"

$PackageWebCoreBegin

void IHttpInvalidRequestAction::invoke(IRequest &request) const
{
    request.startWrite();
}

$PackageWebCoreEnd
