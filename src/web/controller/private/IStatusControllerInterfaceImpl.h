#pragma once
#include "core/base/IHeaderUtil.h"
#include "web/node/IStatusActionNode.h"

$PackageWebCoreBegin

struct IControllerInfo;
namespace IStatusControllerInterfaceImpl
{
    QVector<IStatusActionNode> generateStatusFunctionNodes(const IControllerInfo& info);
    void checkStatusNodes(const QVector<IStatusActionNode>& nodes);

    void checkStatusType(const IStatusActionNode& node);
    void checkReturnType(const IStatusActionNode& node);
    void checkInputArgs(const IStatusActionNode& node);
};

$PackageWebCoreEnd
