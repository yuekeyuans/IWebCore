#pragma once
#include "core/util/IHeaderUtil.h"
#include "IParameterNode.h"

$PackageWebCoreBegin

struct IMethodNode
{
public:
    void* handler{nullptr};
    QMetaMethod metaMethod;

    QString className;
    QString functionName;
    QString signature;

    QString returnTypeName;
    QMetaType::Type returnTypeId {QMetaType::UnknownType};

    int parameterCount;
    QVector<IParameterNode> paramNodes;
    QStringList parameterNames;
    QStringList parameterTypeNames;
    QList<QMetaType::Type> parameterTypeIds;
};

$PackageWebCoreEnd
