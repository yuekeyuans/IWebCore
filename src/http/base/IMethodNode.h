#pragma once
#include "core/util/IHeaderUtil.h"
#include "IArgumentTypeNode.h"
#include "IReturnTypeNode.h"

$PackageWebCoreBegin

struct IMethodNode
{
public:
    void* handler{nullptr};
    QMetaMethod metaMethod;

    QString className;
    QString functionName;
    QString signature;

    IReturnTypeNode returnNode;
    QVector<IArgumentTypeNode> paramNodes;
//    int parameterCount;
//    QStringList parameterNames;
//    QStringList parameterTypeNames;
//    QList<QMetaType::Type> parameterTypeIds;
};

$PackageWebCoreEnd
