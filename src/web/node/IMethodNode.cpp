#include "IMethodNode.h"

#include "base/IPackageUtil.h"
#include "web/controller/private/IControllerInfo.h"
#include "web/IWebAssert.h"

$PackageWebCoreBegin

$UseAssert(IWebAssert)

static const QString& nmspace = $PackageWebCoreName;

namespace IMethodNodeHelper
{
    void assignBaseInfo(IMethodNode& node, void* handle, QMetaMethod method);
    void createFunctionExpression(IMethodNode& node);
    void createFunctionParamNodes(IMethodNode& node, QMetaMethod method);
};

IMethodNode IMethodNode::fromMetaMethod(void *handler, const QString &className, const QMetaMethod &method)
{
    IMethodNode node;
    node.className = className;
    IMethodNodeHelper::assignBaseInfo(node, handler, method);
    IMethodNodeHelper::createFunctionParamNodes(node, method);
    IMethodNodeHelper::createFunctionExpression(node);

    return node;
}

int IMethodNode::getParamCount() const
{
    return paramNodes.count();
}

QStringList IMethodNode::getParamNames() const
{
    QStringList ret;
    for(const auto& param : paramNodes){
        ret.append(param.paramName);
    }

    return ret;
}

QStringList IMethodNode::getParamTypeNames() const
{
    QStringList ret;
    for(const auto& param : paramNodes){
        ret.append(param.paramTypeName);
    }

    return ret;
}

QList<QMetaType::Type> IMethodNode::getParamTypeIds() const
{
    QList<QMetaType::Type> ret;
    for(const auto& param : paramNodes){
        ret.append(QMetaType::Type(param.paramTypeId));
    }

    return ret;
}

void IMethodNodeHelper::assignBaseInfo(IMethodNode& node, void* handle, QMetaMethod method)
{
    node.handler = handle;
    node.metaMethod = method;
    node.funName = method.name();
    node.returnTypeName = method.typeName();
    node.returnTypeId = QMetaType::Type(method.returnType());

    // return type
    if(node.returnTypeId == QMetaType::UnknownType){
        IAssertInfo info;
        info.reason = QString("return Type Not Defined in QMeta System. type: ").append(node.returnTypeName)
                           .append(", Function: ").append(node.expression);
        $Ast->fatal("controller_invalid_parameter_type", info);
    }
}

void IMethodNodeHelper::createFunctionExpression(IMethodNode& node)
{
    QString expression;
    expression.append(node.returnTypeName).append(' ');
    expression.append(node.className).append("::").append(node.funName).append("(");

    QStringList args;
    for(const auto& param : node.paramNodes){
        auto arg = QString(param.paramTypeName).append(' ').append(param.paramName);
        args.append(arg);
    }

    expression.append(args.join(", ")).append(")");
    node.expression = expression;
}

void IMethodNodeHelper::createFunctionParamNodes(IMethodNode& node, QMetaMethod method)
{
    auto names = method.parameterNames();
    auto types = method.parameterTypes();
    auto ids = QVector<QMetaType::Type>();

    for(int i=0;i<method.parameterCount(); i++){
        auto id = method.parameterType(i);
        if(id == QMetaType::UnknownType){
            IAssertInfo info;
            info.reason = QString("parameter Type Not Defined in QMeta System. type: ").append(types[i])
                              .append(", Function: ").append(node.expression);
            $Ast->fatal("controller_invalid_parameter_type", info);

        }else{
            ids.append(QMetaType::Type(id));
        }
    }

    for(int i=0; i<method.parameterCount(); i++){
        IParamNode paramNode;
        paramNode.paramName = names[i];
        paramNode.paramTypeName = types[i];
        paramNode.paramTypeId = ids[i];
        node.paramNodes.append(paramNode);
    }
}

$PackageWebCoreEnd
