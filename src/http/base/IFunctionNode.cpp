#include "IFunctionNode.h"
#include "core/util/ISpawnUtil.h"

$PackageWebCoreBegin

IFunctionNode IFunctionNode::createFunctionNode(std::function<void(const IRequest &, IResponse&)> functor)
{
    IFunctionNode node;
    node.function = functor;
    node.returnTypeId = QMetaType::Type::Void;
    node.funParamCount = 2;

    IParameterNode reqNode = ISpawnUtil::construct<IParameterNode, int, QString, QString>(QMetaType::type("IRequest&"), "IRequest&", "request", QByteArray("functionNode"));
    IParameterNode resNode = ISpawnUtil::construct<IParameterNode>(QMetaType::type("IResponse&"), "IResponse&", "response", QByteArray("functionNode"));
    node.funParamNodes.append(reqNode);
    node.funParamNodes.append(resNode);

    return node;
}

$PackageWebCoreEnd
