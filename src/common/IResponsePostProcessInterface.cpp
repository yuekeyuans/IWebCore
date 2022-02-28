#include "IResponsePostProcessInterface.h"
#include "common/net/IResponse.h"

$PackageWebCoreBegin

IResponsePostProcessInterface::IResponsePostProcessInterface()
{

}

bool IResponsePostProcessInterface::match(const IRequest &request, const IResponse & response)
{
    Q_UNUSED(request);
    Q_UNUSED(response);

    return false;
}

void IResponsePostProcessInterface::process(IRequest &request, IResponse &response)
{
    Q_UNUSED(request)
    Q_UNUSED(response)
}

$PackageWebCoreEnd
