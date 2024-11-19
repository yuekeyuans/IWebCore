#include "IHttpBadRequestInvalid.h"

$PackageWebCoreBegin

IHttpBadRequestInvalid::IHttpBadRequestInvalid()
    : IHttpInvalidInterface(IHttpStatus::BAD_REQUEST_400)
{
}

IHttpBadRequestInvalid::IHttpBadRequestInvalid(const QString &description)
    : IHttpInvalidInterface(IHttpStatus::BAD_REQUEST_400, description)
{
}

void IHttpBadRequestInvalid::process(IRequest &request)
{
    qDebug() << "invoke here";
}

$PackageWebCoreEnd
