#pragma once
#include "core/util/IHeaderUtil.h"
#include "IArgumentType.h"
#include "IReturnType.h"

$PackageWebCoreBegin

struct IMethodNode
{
public:
    void* handler{nullptr};
    QString className;
    QMetaMethod metaMethod;

    QString signature;
    IReturnType returnNode;
    QVector<IArgumentType> argumentNodes;
};

$PackageWebCoreEnd
