#pragma once
#include "base/IHeaderUtil.h"

$PackageWebCoreBegin

struct IFunctionParamNode{
    int paramTypeId;
    QString paramType;
    QString paramName;
};

struct IFunctionNode
{
    void* handler{nullptr};
    int funParamCount{0};
    QMetaMethod metaMethod;
    QString funName;
    QString funRetunType;
    QMetaType::Type funReturnTypeId {QMetaType::UnknownType};
    QList<QByteArray> funParamNames;
    QList<QByteArray> funParamTypes;
    QList<QMetaType::Type> funParamTypeIds;
    QVector<IFunctionParamNode> funParamNodes;

    QString funExpression;

    static IFunctionNode fromMetaMethod(void* handle, QMetaMethod method);
};

$PackageWebCoreEnd
