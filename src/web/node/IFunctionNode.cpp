#include "IFunctionNode.h"

$PackageWebCoreBegin

    IFunctionNode IFunctionNode::createFunctionNode(std::function<void(const IRequest &, IResponse&)> functor)
{
    IFunctionNode node;
    node.function = functor;
    node.returnTypeId = QMetaType::Type::Void;
    node.funParamCount = 2;

    IParamNode reqNode;
    reqNode.paramName = "request";
    reqNode.paramTypeName = "IRequest&";
    reqNode.paramTypeId = QMetaType::type("IRequest&");
    node.funParamNodes.append(reqNode);

    IParamNode resNode;
    resNode.paramName = "response";
    resNode.paramTypeName = "IResponse&";
    resNode.paramTypeId = QMetaType::type("IResponse&");
    node.funParamNodes.append(resNode);

    return node;
}

$PackageWebCoreEnd
