#include "IMiddleWare.h"
#include "core/base/IConstantUtil.h"
#include "web/net/IRequest.h"
#include "web/net/IResponse.h"

$PackageWebCoreBegin

bool IMiddleWare::operator()(IRequest &request, IResponse &response)
{
    return action(request, response);
}

$PackageWebCoreEnd

