#include "IHttpInternalErrorAction.h"
#include "http/IRequest.h"
#include "http/invalid/IHttpInternalErrorInvalid.h"

$PackageWebCoreBegin

void IHttpInternalErrorAction::invoke(IRequest &request) const
{
    request.setInvalid(IHttpInternalErrorInvalid());
    request.startWrite();
}

$PackageWebCoreEnd
