#include "IServerNameMiddleWare.h"
#include "common/net/IResponse.h"

$PackageWebCoreBegin

IServerNameMiddleWare::IServerNameMiddleWare()
{
}

bool IServerNameMiddleWare::match(IRequest &request, IResponse &response)
{
    Q_UNUSED(request)
    Q_UNUSED(response)

    return true;
}

bool IServerNameMiddleWare::action(IRequest &request, IResponse &response)
{
    Q_UNUSED(request)

    response["Server"] = "iwebcore";
    return true;
}

$PackageWebCoreEnd
