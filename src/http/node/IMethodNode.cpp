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
    detail::resolveParamNode(node);
    detail::createFunctionExpression(node);

    return node;
}

int IMethodNode::getParamCount() const
{
    return paramNodes.count();
}

const QStringList& IMethodNode::getParamNames() const
{
    return m_paramNames;
}

const QStringList& IMethodNode::getParamTypeNames() const
{
    return m_paramTypeNames;
}

const QStringList &IMethodNode::getParamQualifiers() const
{
    return m_paramQualifiers;
}

const QList<QMetaType::Type>& IMethodNode::getParamTypeIds() const
{
    return m_paramTypeIds;
}

void detail::assignBaseInfo(IMethodNode& node, void* handle, QMetaMethod method)
{
    node.handler = handle;
    node.metaMethod = method;
    node.funName = method.name();
    node.returnTypeName = method.typeName();
    node.returnTypeId = QMetaType::Type(method.returnType());

    if(node.returnTypeId == QMetaType::UnknownType){ // return type
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
    for(int i=0; i<node.paramNodes.length(); i++){
        args.append(node.getParamTypeNames()[i] + " " + node.getParamNames()[i]);
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
        node.m_paramTypeNames.append(param.paramTypeName);
        node.m_paramTypeIds.append(QMetaType::Type(param.paramTypeId));

        auto args = param.paramName.split("_$");
        node.m_paramNames.append(args.first());
        args.pop_front();
        node.m_paramQualifiers.append(args);
    }
}

$PackageWebCoreEnd
