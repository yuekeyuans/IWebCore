#include "IFunctionNode.h"
#include "assertion/IAssertPreProcessor.h"

$PackageWebCoreBegin

static const QString& nmspace = $PackageWebCoreName;

namespace IFunctionNodeHelper{
void assignBaseInfo(IFunctionNode& node, void* handle, QMetaMethod method);
QString createFunctionExpression(IFunctionNode& node);
void createFunctionParamNodes(IFunctionNode& node);
};

IFunctionNode IFunctionNode::fromMetaMethod(void *handle, QMetaMethod method)
{
    IFunctionNode node;

    IFunctionNodeHelper::assignBaseInfo(node, handle, method);
    IFunctionNodeHelper::createFunctionParamNodes(node);

    return node;
}

void IFunctionNodeHelper::assignBaseInfo(IFunctionNode& node, void* handle, QMetaMethod method)
{
    node.handler = handle;
    node.metaMethod = method;
    node.funName = method.name();
    node.funParamCount = method.parameterCount();
    node.funParamNames = method.parameterNames();
    node.funParamTypes = method.parameterTypes();
    node.funRetunType = method.typeName();
    node.funReturnTypeId = QMetaType::Type(method.returnType());
    node.funExpression = IFunctionNodeHelper::createFunctionExpression(node);

    if(node.funReturnTypeId == QMetaType::UnknownType){
        QString info = QString("return Type Not Defined in QMeta System. type: ").append(node.funRetunType)
                           .append(", Function: ").append(node.funExpression);
        $AssertFatal(controller_invalid_parameter_type, info)
    }

    for(int i=0;i<node.funParamCount; i++){
        auto id = method.parameterType(i);
        if(id == QMetaType::UnknownType){
            QString info = QString("parameter Type Not Defined in QMeta System. type: ").append(node.funParamTypes[i])
                               .append(", Function: ").append(node.funExpression);
            $AssertFatal(controller_invalid_parameter_type, info);
        }else{
            node.funParamTypeIds.append(QMetaType::Type(id));
        }
    }
}

QString IFunctionNodeHelper::createFunctionExpression(IFunctionNode& node)
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

void IFunctionNodeHelper::createFunctionParamNodes(IFunctionNode& node)
{
    for(int i=0; i<node.funParamCount; i++){
        IFunctionParamNode paramNode;
        paramNode.paramName = node.funParamNames[i];
        paramNode.paramTypeId = node.funParamTypeIds[i];
        paramNode.paramType = node.funParamTypes[i];
        node.funParamNodes.append(paramNode);
    }
}

$PackageWebCoreEnd
