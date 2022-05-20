#include "IDefaultStatusController.h"
#include "web/net/IRequest.h"
#include "web/net/IResponse.h"

$PackageWebCoreBegin

void IDefaultStatusController::handle404Page(IRequest &request, IResponse &response)
{
    Q_UNUSED(request);
    response.setContent("hello world");
}

$PackageWebCoreEnd
