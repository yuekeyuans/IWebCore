#include "IFunctionNode.h"

$PackageWebCoreBegin

IFunctionNode IFunctionNode::createFunctionNode(std::function<void(const IRequest &, IResponse&)> functor)
{
    IFunctionNode node;
    node.function = functor;
    node.returnTypeId = QMetaType::Type::Void;
    node.funParamCount = 2;

    IParamNode reqNode = IParamNodeHelper::createParamNode(QMetaType::type("IRequest&"), "IRequest&", "request");
    node.funParamNodes.append(reqNode);
    IParamNode resNode = IParamNodeHelper::createParamNode(QMetaType::type("IResponse&"), "IResponse&", "response");
    node.funParamNodes.append(resNode);

    return node;
}

$PackageWebCoreEnd
