#pragma once
#include "base/IHeaderUtil.h"
#include "IParamNode.h"

$PackageWebCoreBegin

struct IMethodNode
{
public:
    static IMethodNode fromMetaMethod(void* handle, QMetaMethod method);
    int getParamCount() const;
    QStringList getParamNames() const;
    QStringList getParamTypeNames() const;
    QList<QMetaType::Type> getParamTypeIds() const;



public:
    void* handler{nullptr};

    QMetaMethod metaMethod;
    QString funName;
    QString expression;

    QString returnTypeName;
    QMetaType::Type returnTypeId {QMetaType::UnknownType};
    QVector<IParamNode> paramNodes;
};

$PackageWebCoreEnd
