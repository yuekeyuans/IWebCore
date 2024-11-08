#pragma once
#include "core/util/IHeaderUtil.h"
#include "IArgumentTypeNode.h"
#include "IReturnTypeNode.h"

$PackageWebCoreBegin

struct IMethodNode
{
public:
    void* handler{nullptr};
    QString className;
    QMetaMethod metaMethod;

    QString signature;
    IReturnTypeNode returnNode;
    QVector<IArgumentTypeNode> argumentNodes;
};

$PackageWebCoreEnd
