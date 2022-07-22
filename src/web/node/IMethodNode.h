#pragma once
#include "base/IHeaderUtil.h"
#include "IParamNode.h"

$PackageWebCoreBegin

struct IMethodNode
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
    QVector<IParamNode> funParamNodes;

    QString funExpression;
    static IMethodNode fromMetaMethod(void* handle, QMetaMethod method);
};

$PackageWebCoreEnd
