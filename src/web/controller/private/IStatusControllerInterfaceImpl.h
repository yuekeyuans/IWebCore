#pragma once
#include "base/IHeaderUtil.h"
#include "web/node/IStatusFunctionNode.h"

$PackageWebCoreBegin

class IStatusControllerInterfaceImpl
{
    $UseInstance(IStatusControllerInterfaceImpl)
public:
    IStatusControllerInterfaceImpl() = default;
    static QVector<IStatusFunctionNode> generateStatusFunctionNodes(void* handle, QMap<QString, QString>clsInfo, QVector<QMetaMethod> methods);
    static void checkStatusNodes(const QVector<IStatusFunctionNode>& nodes);

private:
    void checkStatusType(const IStatusFunctionNode& node);
    void checkReturnType(const IStatusFunctionNode& node);
    void checkInputArgs(const IStatusFunctionNode& node);
};


$PackageWebCoreEnd
