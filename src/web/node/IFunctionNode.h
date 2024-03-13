#pragma once

#include "core/base/IHeaderUtil.h"
#include "IParamNode.h"
#include "web/net/IRequest.h"
#include "web/net/IResponse.h"

$PackageWebCoreBegin

struct IFunctionNode
{
public:
    static IFunctionNode createFunctionNode(std::function<void(const IRequest&, IResponse&)>);

public:
    int returnTypeId {QMetaType::Void};
    int funParamCount{0};
    QVector<IParamNode> funParamNodes;
    std::function<void(IRequest&,  IResponse&)> function;
};

$PackageWebCoreEnd
