#include "IMiddleWare.h"
#include "core/base/IConstantUtil.h"
#include "http/net/IRequest.h"
#include "http/net/IResponse.h"

$PackageWebCoreBegin

bool IMiddleWare::operator()(IRequest &request, IResponse &response)
{
    return action(request, response);
}

$PackageWebCoreEnd

