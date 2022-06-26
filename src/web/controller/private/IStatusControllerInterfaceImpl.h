#pragma once
#include "base/IHeaderUtil.h"
#include "web/node/IStatusFunctionNode.h"

$PackageWebCoreBegin

namespace IStatusControllerInterfaceImpl
{
    QVector<IStatusFunctionNode> generateStatusFunctionNodes(void* handle, QMap<QString, QString>clsInfo, QVector<QMetaMethod> methods);
    void checkStatusNodes(const QVector<IStatusFunctionNode>& nodes);

    void checkStatusType(const IStatusFunctionNode& node);
    void checkReturnType(const IStatusFunctionNode& node);
    void checkInputArgs(const IStatusFunctionNode& node);
};

$PackageWebCoreEnd
