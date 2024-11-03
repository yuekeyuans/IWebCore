#include "IHttpNotFoundAction.h"
#include "http/invalid/IHttpNotFoundInvalid.h"
#include "http/net/IRequest.h"
#include "http/server/IHttpConnection.h"

$PackageWebCoreBegin

void IHttpNotFoundAction::invoke(IRequest &request) const
{
    Q_UNUSED(request)
    qDebug() << "invoke here";

    request.setInvalid(IHttpNotFoundInvalid());
    // TODO: 这里需要查看一下 invalid 的实现，到底是为啥
    request.m_connection->doWrite();
}

$PackageWebCoreEnd
