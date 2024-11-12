#include "IMethodNode.h"

#include "core/util/IPackageUtil.h"
#include "core/util/ISpawnUtil.h"
#include "core/abort/IAbortInterface.h"

$PackageWebCoreBegin

class IMethodNodeAbort : public IAbortInterface<IMethodNodeAbort>
{
    $AsAbort(controller_invalid_parameter_type)
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
    void createReturnNode();
    void createArgumentNodes();
    void createSignature();

private:
    void checkMethodOfReturnVoid();
};

IMethodNodeDetail::IMethodNodeDetail(void *handler_, const QString &className_, const QMetaMethod &method_)
    : IMethodNode{handler_, className_, method_}
{
    createReturnNode();
    createArgumentNodes();
    createSignature();

    checkMethodOfReturnVoid();
}

void IMethodNodeDetail::createReturnNode()
{
    returnNode = ISpawnUtil::construct<IReturnTypeNode>(metaMethod.returnType(), metaMethod.typeName());
}

void IMethodNodeDetail::createArgumentNodes()
{
    auto names = metaMethod.parameterNames();
    auto types = metaMethod.parameterTypes();

    for(int i=0;i<metaMethod.parameterCount(); i++){
        auto id = metaMethod.parameterType(i);
        if(id == QMetaType::UnknownType){
            auto reason = QString("unknown registered type: ").append(types[i])
                              .append(", Function: ").append(className).append("::").append(metaMethod.name());
            IMethodNodeAbort::abortcontroller_invalid_parameter_type(reason, $ISourceLocation);
        }

        argumentNodes.append(ISpawnUtil::construct<IArgumentTypeNode>(id, types[i], names[i], metaMethod.methodSignature()));
    }
}

void IMethodNodeDetail::createSignature()
{
    QStringList args;
    for(const IArgumentTypeNode& node : argumentNodes){
        args.append(node.typeName + " " + node.name);
    }

    signature.append(returnNode.typeName).append(' ')
            .append(className).append("::").append(metaMethod.name()).append("(")
            .append(args.join(", ")).append(")");
}

void IMethodNodeDetail::checkMethodOfReturnVoid()
{
    if(returnNode.typeId != QMetaType::Void){
        return;
    }
    static const QStringList s_nodeNames ={
        "IResponse", "IResponse&", "IRequest", "IRequest&"
    };
    for(const IArgumentTypeNode& info : argumentNodes){
        if(s_nodeNames.contains(info.typeName)){
            return;
        }
    }

    QString info = "mapping function that return void should include IResponse in side function parameters\n"
                   "at Function : " + signature;
    qFatal(info.toUtf8());
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
