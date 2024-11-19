#include "IHttpNotFoundAction.h"
#include "http/invalid/IHttpNotFoundInvalid.h"
#include "http/net/IRequest.h"
#include "http/server/IHttpConnection.h"

$PackageWebCoreBegin

void IHttpNotFoundAction::invoke(IRequest &request) const
{
    request.setInvalid(IHttpNotFoundInvalid());
    request.doWrite();
}

$PackageWebCoreEnd
