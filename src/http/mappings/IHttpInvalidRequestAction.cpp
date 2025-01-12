#include "IHttpInvalidRequestAction.h"
#include "http/net/IRequest.h"

$PackageWebCoreBegin

void IHttpInvalidRequestAction::invoke(IRequest &request) const
{
    qDebug() << __FUNCTION__ << request.isValid() << request.m_data.m_data;
    request.startWrite();
}

$PackageWebCoreEnd
