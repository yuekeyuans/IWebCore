#pragma once

#include "base/IHeaderUtil.h"
#include "IParamNode.h"
#include "web/net/IRequest.h"
#include "web/net/IResponse.h"

$PackageWebCoreBegin


// this mean static function, static member function, lambda function that is void(IRequest&, IResponse)

struct IFunctionNode
{
    std::function<void(IRequest&,  IResponse&)> function;

    int funParamCount{0};
    QVector<IParamNode> funParamNodes;
};

$PackageWebCoreEnd
