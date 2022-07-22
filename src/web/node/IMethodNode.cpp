#include "IMethodNode.h"

#include "base/IPackageUtil.h"
#include "web/IWebAssert.h"

$PackageWebCoreBegin

$UseAssert(IWebAssert)

static const QString& nmspace = $PackageWebCoreName;

namespace IMethodNodeHelper
{
    void assignBaseInfo(IMethodNode& node, void* handle, QMetaMethod method);
    QString createFunctionExpression(IMethodNode& node);
    void createFunctionParamNodes(IMethodNode& node);
};

IMethodNode IMethodNode::fromMetaMethod(void *handle, QMetaMethod method)
{
    IMethodNode node;

    IMethodNodeHelper::assignBaseInfo(node, handle, method);
    IMethodNodeHelper::createFunctionParamNodes(node);

    return node;
}

void IMethodNodeHelper::assignBaseInfo(IMethodNode& node, void* handle, QMetaMethod method)
{
    node.handler = handle;
    node.metaMethod = method;
    node.funName = method.name();
    node.funParamCount = method.parameterCount();
    node.funParamNames = method.parameterNames();
    node.funParamTypes = method.parameterTypes();
    node.funRetunType = method.typeName();
    node.funReturnTypeId = QMetaType::Type(method.returnType());
    node.funExpression = IMethodNodeHelper::createFunctionExpression(node);

    if(node.funReturnTypeId == QMetaType::UnknownType){
        IAssertInfo info;
        info.reason = QString("return Type Not Defined in QMeta System. type: ").append(node.funRetunType)
                           .append(", Function: ").append(node.funExpression);
        $Ast->fatal("controller_invalid_parameter_type", info);
    }

    for(int i=0;i<node.funParamCount; i++){
        auto id = method.parameterType(i);
        if(id == QMetaType::UnknownType){
            IAssertInfo info;
            info.reason = QString("parameter Type Not Defined in QMeta System. type: ").append(node.funParamTypes[i])
                               .append(", Function: ").append(node.funExpression);
            $Ast->fatal("controller_invalid_parameter_type", info);
        }else{
            node.funParamTypeIds.append(QMetaType::Type(id));
        }
    }
}

QString IMethodNodeHelper::createFunctionExpression(IMethodNode& node)
{
    QString expression;
    expression.append(node.funRetunType).append(' ');
    expression.append(node.funName).append("(");

    QStringList args;

    for(int i=0; i<node.funParamCount; i++){
        QString arg;
        arg.append(node.funParamTypes[i]).append(' ').append(node.funParamNames[i]);
        args.append(arg);
    }

    expression.append(args.join(", ")).append(")");
    return expression;
}

void IMethodNodeHelper::createFunctionParamNodes(IMethodNode& node)
{
    for(int i=0; i<node.funParamCount; i++){
        IParamNode paramNode;
        paramNode.paramName = node.funParamNames[i];
        paramNode.paramTypeId = node.funParamTypeIds[i];
        paramNode.paramType = node.funParamTypes[i];
        node.funParamNodes.append(paramNode);
    }
}

$PackageWebCoreEnd
