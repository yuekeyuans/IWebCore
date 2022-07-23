#pragma once
#include "base/IHeaderUtil.h"
#include "IParamNode.h"

$PackageWebCoreBegin

struct IMethodNode
{
    void* handler{nullptr};

    QMetaMethod metaMethod;

    QString funName;

    QString returnTypeName;
    QMetaType::Type returnTypeId {QMetaType::UnknownType};

    int paramCount{0};
    QList<QByteArray> paramNames;
    QList<QByteArray> paramTypeNames;
    QList<QMetaType::Type> paramTypeIds;

    QVector<IParamNode> paramNodes;

    QString expression;
    static IMethodNode fromMetaMethod(void* handle, QMetaMethod method);
};

$PackageWebCoreEnd
