#pragma once
#include "core/util/IHeaderUtil.h"
#include "IParamNode.h"

$PackageWebCoreBegin

struct IHttpControllerInfo;

struct IMethodNode
{
public:
    int getParamCount() const;
    const QStringList& getParamNames() const;
    const QStringList& getParamTypeNames() const;
    const QList<QMetaType::Type>& getParamTypeIds() const;

public:
    void* handler{nullptr};
    QString className;
    QMetaMethod metaMethod;

    QString funName;
    QString expression;

    QString returnTypeName;
    QMetaType::Type returnTypeId {QMetaType::UnknownType};
    QVector<IParamNode> paramNodes;

public:
    QStringList paramNames;
    QStringList paramTypeNames;
    QList<QMetaType::Type> paramTypeIds;
};

namespace  IMethodNodeHelper
{
    IMethodNode fromMetaMethod(void* handler, const QString& className, const QMetaMethod& method);
}

$PackageWebCoreEnd
