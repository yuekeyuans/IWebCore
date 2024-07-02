#include "IMethodNode.h"

#include "core/util/IPackageUtil.h"
#include "core/abort/IAbortInterface.h"
#include "http/controller/private/IHttpControllerInfo.h"

$PackageWebCoreBegin

static const QString& nmspace = $PackageWebCoreName;

class IMethodNodeAbort : public IAbortInterface<IMethodNodeAbort>
{
    $AsAbort(
        controller_invalid_parameter_type
    )
protected:
    virtual QMap<int, QString> abortDescription() const final{
        return {
            {controller_invalid_parameter_type, ""},
        };
    }
};

class IMethodNodeDetail : public IMethodNode
{
public:
    IMethodNodeDetail(void *handler, const QString &className, const QMetaMethod &metaMethod);

public:
    void assignBaseInfo();
    void createFunctionExpression();
    void createFunctionParamNodes();
    void resolveParamNode();
};



inline IMethodNodeDetail::IMethodNodeDetail(void *handler_, const QString &className_, const QMetaMethod &method_)
{
    this->handler = handler_;
    this->className = className_;
    this->metaMethod = method_;

    assignBaseInfo();
    createFunctionParamNodes();
    resolveParamNode();
    createFunctionExpression();
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

const QList<QMetaType::Type>& IMethodNode::getParamTypeIds() const
{
    return paramTypeIds;
}

inline void IMethodNodeDetail::assignBaseInfo()
{
    funName = metaMethod.name();
    returnTypeName = metaMethod.typeName();
    returnTypeId = QMetaType::Type(metaMethod.returnType());

    if(returnTypeId == QMetaType::UnknownType){ // return type
        auto reason = QString("return Type Not Defined in QMeta System. type: ").append(returnTypeName)
                           .append(", Function: ").append(expression);
        IMethodNodeAbort::abortcontroller_invalid_parameter_type(reason, $ISourceLocation);
    }
}

inline void IMethodNodeDetail::createFunctionExpression()
{
    QString exp;
    exp.append(returnTypeName).append(' ');
    exp.append(className).append("::").append(funName).append("(");

    QStringList args;
    for(int i=0; i<paramNodes.length(); i++){
        args.append(getParamTypeNames()[i] + " " + getParamNames()[i]);
    }

    exp.append(args.join(", ")).append(")");
    expression = exp;
}

inline void IMethodNodeDetail::createFunctionParamNodes()
{
    auto names = metaMethod.parameterNames();
    auto types = metaMethod.parameterTypes();

    for(int i=0;i<metaMethod.parameterCount(); i++){
        auto id = metaMethod.parameterType(i);
        if(id == QMetaType::UnknownType){
            auto reason = QString("parameter Type Not Defined in QMeta System. type: ").append(types[i])
                              .append(", Function: ").append(className).append("::").append(funName);
            IMethodNodeAbort::abortcontroller_invalid_parameter_type(reason, $ISourceLocation);
        }

        auto node = ISpawnUtil::construct<IParamNode>(id, types[i], names[i]);
        paramNodes.append(node);
//        paramNodes.append(IParamNodeHelper::createParamNode(id, types[i], names[i]));
    }
}

inline void IMethodNodeDetail::resolveParamNode()
{
    for(const IParamNode& param : paramNodes){
        paramTypeNames.append(param.paramTypeName);
        paramTypeIds.append(QMetaType::Type(param.paramTypeId));
        paramNames.append(param.paramName);
    }
}

namespace ISpawnUtil
{
    template<>
    IMethodNode construct(void *handler, QString className, QMetaMethod method)
    {
        return IMethodNodeDetail(handler, className, method);
    }
}

//IMethodNode IMethodNodeHelper::fromMetaMethod(void *handler, const QString &className, const QMetaMethod &method)
//{
//    return IMethodNodeDetail(handler, className, method);
//}

$PackageWebCoreEnd
