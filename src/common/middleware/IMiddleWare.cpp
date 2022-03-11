#include "IMiddleWare.h"
#include "base/IConstantUtil.h"
#include "common/net/IRequest.h"
#include "common/net/IResponse.h"

$PackageWebCoreBegin

bool IMiddleWare::operator()(IRequest &request, IResponse &response)
{
    return action(request, response);
}

$PackageWebCoreEnd

