#include "IDefaultStatusController.h"
#include "common/net/IRequest.h"
#include "common/net/IResponse.h"

$PackageWebCoreBegin

void IDefaultStatusController::handle404Page(IRequest &request, IResponse &response)
{
    Q_UNUSED(request);
    response.setContent("hello world");
}

$PackageWebCoreEnd
