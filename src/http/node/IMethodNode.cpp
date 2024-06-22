#include "IMethodNode.h"

#include "core/base/IPackageUtil.h"
#include "http/controller/private/IHttpControllerInfo.h"
#include "http/IHttpAssert.h"

$PackageWebCoreBegin

$UseAssert(IHttpAssert)

static const QString& nmspace = $PackageWebCoreName;

namespace detail
{
    void assignBaseInfo(IMethodNode& node, void* handle, QMetaMethod method);
    void createFunctionExpression(IMethodNode& node);
    void createFunctionParamNodes(IMethodNode& node, QMetaMethod method);
    void resolveParamNode(IMethodNode& node);
}

IMethodNode IMethodNode::fromMetaMethod(void *handler, const QString &className, const QMetaMethod &method)
{
    IMethodNode node;
    node.className = className;
    detail::assignBaseInfo(node, handler, method);
    detail::createFunctionParamNodes(node, method);
    detail::createFunctionExpression(node);
    detail::resolveParamNode(node);

    return node;
}

int IMethodNode::getParamCount() const
{
    return paramNodes.count();
}

const QStringList& IMethodNode::getParamNames() const
{
    return paramNames;
}

const QStringList& IMethodNode::getParamTypeNames() const
{
    return paramTypeNames;
}

const QStringList &IMethodNode::getParamQualifiers() const
{
    return paramQualifiers;
}

const QList<QMetaType::Type>& IMethodNode::getParamTypeIds() const
{
    return paramTypeIds;
}

void detail::assignBaseInfo(IMethodNode& node, void* handle, QMetaMethod method)
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

void detail::createFunctionExpression(IMethodNode& node)
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

void detail::createFunctionParamNodes(IMethodNode& node, QMetaMethod method)
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

void detail::resolveParamNode(IMethodNode &node)
{
    for(const IParamNode& param : node.paramNodes){
        node.paramTypeNames.append(param.paramTypeName);
        node.paramTypeIds.append(QMetaType::Type(param.paramTypeId));

        auto args = param.paramName.split("_$");
        node.paramNames.append(args.first());
        args.pop_front();
        node.paramQualifiers.append(args);
    }
}

$PackageWebCoreEnd
