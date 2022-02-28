#include "IRequestErrorPreIntercept.h"
#include "common/net/IRequest.h"
#include "common/net/IResponse.h"
#include "common/response/IStatusCodeResponse.h"

$PackageWebCoreBegin

bool IRequestErrorPreIntercept::match(const IRequest &request)
{
    return !request.valid();
}

void IRequestErrorPreIntercept::intercept(IRequest &request, IResponse & response)
{
    Q_UNUSED(request)
    response.respond();
}

$PackageWebCoreEnd
