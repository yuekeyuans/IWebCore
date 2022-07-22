#pragma once
#include "base/IHeaderUtil.h"
#include "web/node/IStatusActionNode.h"

$PackageWebCoreBegin

namespace IStatusControllerInterfaceImpl
{
    QVector<IStatusActionNode> generateStatusFunctionNodes(void* handle, QMap<QString, QString>clsInfo, QVector<QMetaMethod> methods);
    void checkStatusNodes(const QVector<IStatusActionNode>& nodes);

    void checkStatusType(const IStatusActionNode& node);
    void checkReturnType(const IStatusActionNode& node);
    void checkInputArgs(const IStatusActionNode& node);
};

$PackageWebCoreEnd
