#include "IResponsePostInterceptInterface.h"

#include "common/net/IResponse.h"

$PackageWebCoreBegin

IResponsePostInterceptInterface::IResponsePostInterceptInterface()
{

}

bool IResponsePostInterceptInterface::match(IRequest &request, const IResponse &)
{
    Q_UNUSED(request)
    return false;
}

void IResponsePostInterceptInterface::intercept(IRequest &request, IResponse &response)
{
    Q_UNUSED(response)
    Q_UNUSED(request)
}

$PackageWebCoreEnd
