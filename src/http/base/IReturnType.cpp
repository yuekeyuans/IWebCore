#include "IReturnType.h"
#include "core/util/ISpawnUtil.h"
#include "core/bean/IBeanTypeManage.h"
#include "http/base/IMethodParameterManage.h"

$PackageWebCoreBegin

class IReturnTypeNodeDetail : public IReturnType
{
public:
    IReturnTypeNodeDetail(QMetaType::Type type, const QString& name);

private:
    void chechMethodSupportedReturnType();
};

IReturnTypeNodeDetail::IReturnTypeNodeDetail(QMetaType::Type type, const QString& name)
    : IReturnType{type, name}
{
    chechMethodSupportedReturnType();
}

void IReturnTypeNodeDetail::chechMethodSupportedReturnType()
{
    if(typeId == QMetaType::UnknownType){
//        auto reason = QString("return Type Not Defined in QMeta System. type: ").append(typeName);
        qFatal("error");
//        IMethodNodeAbort::abortcontroller_invalid_parameter_type(reason, $ISourceLocation);
    }

    const static QString info = "this kind of return type not supported, please change the return type!";

    const static  QVector<QMetaType::Type> validMetaType = {
        QMetaType::Void,
        QMetaType::Int,
        QMetaType::QString,
//        QMetaType::QJsonArray,
//        QMetaType::QJsonObject,
//        QMetaType::QJsonValue,
//        QMetaType::QByteArray,
        //        QMetaType::QStringList,
    };

    if(validMetaType.contains(typeId)){
        return;
    }

    if(IBeanTypeManage::instance()->isBeanIdExist(typeId)){
        return;
    }

    // TODO: 这个不能这样判断，应为用户可能不按照这个名字写转换
    if(typeName.startsWith("I") && typeName.endsWith("Response")){
        return;
    }

    if(typeId == QMetaType::UnknownType){
//        auto errorInfo = info + "the error take place in Function : " + node.methodNode.signature;
        qFatal("error");
    }

//    auto errorInfo = info + "the error take place in Function : " + node.methodNode.signature;
    qFatal("error");
}

namespace ISpawnUtil
{
    template<>
    IReturnType construct(int type, const char* name)
    {
        return IReturnTypeNodeDetail(QMetaType::Type(type), name);
    }
}

IReturnType::IReturnType(QMetaType::Type type, const QString &name)
    :IMetaType{type, name}
{
    if(IMethodParameterManage::instance()->m_createReturnFun.contains(*this)){
        m_createFun = IMethodParameterManage::instance()->m_createReturnFun[*this];
    }

    if(IMethodParameterManage::instance()->m_destroyReturnFun.contains(*this)){
        m_destroyFun = IMethodParameterManage::instance()->m_destroyReturnFun[*this];
    }
}

void *IReturnType::create() const
{
    return m_createFun();
}

void IReturnType::destroy(void *ptr) const
{
    return m_destroyFun(ptr);
}

void IReturnType::resolveValue(IRequest &request, void *ptr) const
{
    return m_resolveFun(request, ptr);
}

$PackageWebCoreEnd
