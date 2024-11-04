#include "IHttpBadRequestAction.h"
#include "http/invalid/IHttpBadRequestInvalid.h"
#include "http/net/IRequest.h"
#include "http/server/IHttpConnection.h"

$PackageWebCoreBegin

void IHttpBadRequestAction::invoke(IRequest &request) const
{
    request.setInvalid(IHttpBadRequestInvalid());
    request.m_connection->doWrite();
}

$PackageWebCoreEnd
