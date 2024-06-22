#pragma once
#include "core/base/IHeaderUtil.h"
#include "IParamNode.h"

$PackageWebCoreBegin

struct IHttpControllerInfo;

struct IMethodNode
{
public:
    static IMethodNode fromMetaMethod(void* handler, const QString& className, const QMetaMethod& method);
    int getParamCount() const;
    const QStringList& getParamNames() const;
    const QStringList& getParamTypeNames() const;
    const QStringList& getParamQualifiers() const;
    const QList<QMetaType::Type>& getParamTypeIds() const;

public:
    void* handler{nullptr};

    QMetaMethod metaMethod;
    QString className;
    QString funName;
    QString expression;

    QStringList paramNames;
    QStringList paramTypeNames;
    QStringList paramQualifiers;
    QList<QMetaType::Type> paramTypeIds;

    QString returnTypeName;
    QMetaType::Type returnTypeId {QMetaType::UnknownType};
    QVector<IParamNode> paramNodes;
};

$PackageWebCoreEnd
