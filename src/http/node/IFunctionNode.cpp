#include "IFunctionNode.h"

$PackageWebCoreBegin

IFunctionNode IFunctionNode::createFunctionNode(std::function<void(const IRequest &, IResponse&)> functor)
{
    IFunctionNode node;
    node.function = functor;
    node.returnTypeId = QMetaType::Type::Void;
    node.funParamCount = 2;

    IParamNode reqNode( QMetaType::type("IRequest&"), "IRequest&", "request");
    node.funParamNodes.append(reqNode);
    IParamNode resNode(QMetaType::type("IResponse&"), "IResponse&", "response");
    node.funParamNodes.append(resNode);

    return node;
}

$PackageWebCoreEnd
