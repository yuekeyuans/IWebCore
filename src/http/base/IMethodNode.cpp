#include "IMethodNode.h"

#include "core/util/IPackageUtil.h"
#include "core/util/ISpawnUtil.h"
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
    void createFunctionParamNodes();
    void createFunctionExpression();
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

inline void IMethodNodeDetail::assignBaseInfo()
{
    functionName = metaMethod.name();
    returnTypeName = metaMethod.typeName();
    returnTypeId = QMetaType::Type(metaMethod.returnType());

    if(returnTypeId == QMetaType::UnknownType){ // return type
        auto reason = QString("return Type Not Defined in QMeta System. type: ").append(returnTypeName)
                           .append(", Function: ").append(signature);
        IMethodNodeAbort::abortcontroller_invalid_parameter_type(reason, $ISourceLocation);
    }
}

inline void IMethodNodeDetail::createFunctionExpression()
{
    QString exp;
    exp.append(returnTypeName).append(' ');
    exp.append(className).append("::").append(functionName).append("(");

    QStringList args;
    for(const IParameterNode& node : paramNodes){
        args.append(node.typeName + " " + node.name);
    }

    exp.append(args.join(", ")).append(")");
    signature = exp;
}

inline void IMethodNodeDetail::createFunctionParamNodes()
{
    auto names = metaMethod.parameterNames();
    auto types = metaMethod.parameterTypes();

    for(int i=0;i<metaMethod.parameterCount(); i++){
        auto id = metaMethod.parameterType(i);
        if(id == QMetaType::UnknownType){
            auto reason = QString("parameter Type Not Defined in QMeta System. type: ").append(types[i])
                              .append(", Function: ").append(className).append("::").append(functionName);
            IMethodNodeAbort::abortcontroller_invalid_parameter_type(reason, $ISourceLocation);
        }

        paramNodes.append(ISpawnUtil::construct<IParameterNode>(id, types[i], names[i], metaMethod.methodSignature()));
    }
}

void IMethodNodeDetail::resolveParamNode()
{
    for(const IParameterNode& param : paramNodes){
        parameterTypeNames.append(param.typeName);
        parameterTypeIds.append(QMetaType::Type(param.typeId));
        parameterNames.append(param.name);
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

$PackageWebCoreEnd
