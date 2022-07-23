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
    node.paramCount = method.parameterCount();
    node.paramNames = method.parameterNames();
    node.paramTypeNames = method.parameterTypes();
    node.returnTypeName = method.typeName();
    node.returnTypeId = QMetaType::Type(method.returnType());
    node.expression = IMethodNodeHelper::createFunctionExpression(node);

    if(node.returnTypeId == QMetaType::UnknownType){
        IAssertInfo info;
        info.reason = QString("return Type Not Defined in QMeta System. type: ").append(node.returnTypeName)
                           .append(", Function: ").append(node.expression);
        $Ast->fatal("controller_invalid_parameter_type", info);
    }

    for(int i=0;i<node.paramCount; i++){
        auto id = method.parameterType(i);
        if(id == QMetaType::UnknownType){
            IAssertInfo info;
            info.reason = QString("parameter Type Not Defined in QMeta System. type: ").append(node.paramTypeNames[i])
                               .append(", Function: ").append(node.expression);
            $Ast->fatal("controller_invalid_parameter_type", info);
        }else{
            node.paramTypeIds.append(QMetaType::Type(id));
        }
    }
}

QString IMethodNodeHelper::createFunctionExpression(IMethodNode& node)
{
    QString expression;
    expression.append(node.returnTypeName).append(' ');
    expression.append(node.funName).append("(");

    QStringList args;

    for(int i=0; i<node.paramCount; i++){
        QString arg;
        arg.append(node.paramTypeNames[i]).append(' ').append(node.paramNames[i]);
        args.append(arg);
    }

    expression.append(args.join(", ")).append(")");
    return expression;
}

void IMethodNodeHelper::createFunctionParamNodes(IMethodNode& node)
{
    for(int i=0; i<node.paramCount; i++){
        IParamNode paramNode;
        paramNode.paramName = node.paramNames[i];
        paramNode.paramTypeId = node.paramTypeIds[i];
        paramNode.paramType = node.paramTypeNames[i];
        node.paramNodes.append(paramNode);
    }
}

$PackageWebCoreEnd
