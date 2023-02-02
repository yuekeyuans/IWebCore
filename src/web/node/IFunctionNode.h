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
    std::function<void(IRequest&,  IResponse&)> function;

    int returnTypeId {QMetaType::Void};

    int funParamCount{0};
    QVector<IParamNode> funParamNodes;
};

$PackageWebCoreEnd
