#include "IReturnTypeNode.h"
#include "core/util/ISpawnUtil.h"

$PackageWebCoreBegin

class IReturnTypeNodeDetail : public IReturnTypeNode
{
public:
    IReturnTypeNodeDetail(QMetaType::Type type, const QString& name);
    void chechMethodSupportedReturnType();
};

IReturnTypeNodeDetail::IReturnTypeNodeDetail(QMetaType::Type type, const QString& name)
    : IReturnTypeNode{type, name}
{
    chechMethodSupportedReturnType();
}

void IReturnTypeNodeDetail::chechMethodSupportedReturnType()
{
//    if(returnNode.typeId == QMetaType::UnknownType){
//        auto reason = QString("return Type Not Defined in QMeta System. type: ").append(returnNode.typeName)
//                           .append(", Function: ").append(signature);
//        IMethodNodeAbort::abortcontroller_invalid_parameter_type(reason, $ISourceLocation);
//    }


//    const static QString info = "this kind of return type not supported, please change the return type!";

//    const static  QVector<QMetaType::Type> validMetaType = {
//        QMetaType::Void,
//        QMetaType::Int,
//        QMetaType::QString,
//        QMetaType::QJsonArray,
//        QMetaType::QJsonObject,
//        QMetaType::QJsonValue,
//        QMetaType::QByteArray,
//        //        QMetaType::QStringList,
//    };


//    const auto& type = node.methodNode.returnNode.typeName;
//    auto id = node.methodNode.returnNode.typeId;

//    if(validMetaType.contains(id)){
//        return;
//    }

//    if(IBeanTypeManage::instance()->isBeanIdExist(id)){
//        return;
//    }

//    if(type.startsWith("I") && type.endsWith("Response")){
//        return;
//    }

//    if(id == QMetaType::UnknownType){
//        auto errorInfo = info + "the error take place in Function : " + node.methodNode.signature;
//        qFatal(errorInfo.toUtf8());
//    }

//    auto errorInfo = info + "the error take place in Function : " + node.methodNode.signature;
//    qFatal(errorInfo.toUtf8());
}

namespace ISpawnUtil
{
    template<>
    IReturnTypeNode construct(int type, const char* name)
    {
        return IReturnTypeNodeDetail(QMetaType::Type(type), name);
    }
}

$PackageWebCoreEnd
