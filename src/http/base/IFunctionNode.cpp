#include "IFunctionNode.h"

$PackageWebCoreBegin

IFunctionNode IFunctionNode::createFunctionNode(std::function<void(const IRequest &, IResponse&)> functor)
{
    IFunctionNode node;
    node.function = functor;
    node.returnTypeId = QMetaType::Type::Void;
    node.funParamCount = 2;

    IParamNode reqNode = ISpawnUtil::construct<IParamNode, int, QString, QString>(QMetaType::type("IRequest&"), "IRequest&", "request");
    IParamNode resNode = ISpawnUtil::construct<IParamNode>(QMetaType::type("IResponse&"), "IResponse&", "response");
    node.funParamNodes.append(reqNode);
    node.funParamNodes.append(resNode);

    return node;
}

$PackageWebCoreEnd
