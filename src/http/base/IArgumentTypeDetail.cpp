﻿#include "IArgumentTypeDetail.h"
#include "core/util/ISpawnUtil.h"
#include "core/bean/IBeanTypeManage.h"
#include "http/controller/IHttpControllerAbort.h"
#include "http/IHttpManage.h"

$PackageWebCoreBegin

// TODO: 这里 Nullable/NotNull 替换为Optional, 具体的参数见文档

IArgumentTypeDetail::IArgumentTypeDetail(int paramTypeId_, QString paramTypeName_, QString name_, QString methodSignature_)
{
    typeId = (QMetaType::Type)paramTypeId_;
    typeName = paramTypeName_.toStdString();
    nameRaw = name_.toStdString();
    m_methodSignature = methodSignature_.toStdString();

    auto args = name_.split("_$");
    name = args.first().toStdString();
    args.pop_front();
    m_paramQualifiers = args;

}


//void IArgumentTypeDetail::checkParamType()
//{
//    if(typeId == QMetaType::UnknownType){
//        IHttpControllerAbort::abortParamErrorOfUnknowType();
//    }
//}

//void IArgumentTypeDetail::checkParamNameEmpty()
//{
//    if(!isEmbendedType() && name.trimmed().isEmpty()){
//        IHttpControllerAbort::abortParamNameEmpty();
//    }
//}

//void IArgumentTypeDetail::checkParamDuplicated()
//{
//    if(m_paramQualifiers.length() != m_paramQualifiers.toSet().size()){
//        IHttpControllerAbort::abortParamQualifersDuplicated();
//    }
//}

//void IArgumentTypeDetail::checkAndSetParamPosition()
//{
//    bool exist{false};
//    for(auto name : QualifierNames){
//        if(m_paramQualifiers.contains(name)){
//            if(exist){
//                IHttpControllerAbort::abortParamPositionDuplicated();
//            }
//            position = Position(QualifierNames.indexOf(name));
//            m_paramQualifiers.removeOne(name);
//            exist = true;
//        }
//    }
//}

//void IArgumentTypeDetail::checkAndSetParamOptional()
//{
//    bool exist{false};
//    if(m_paramQualifiers.contains(NullableName)){
//        optional = true;
//        m_paramQualifiers.removeAll(NullableName);
//        exist = true;
//    }
//    if(m_paramQualifiers.contains(NotnullName)){
//        if(exist){
//            IHttpControllerAbort::abortParamNullableConflict();
//        }
//        optional = false;
//        m_paramQualifiers.removeAll(NotnullName);
//    }
//}

////void IArgumentTypeNodeDetail::checkAndSetParamRestrictions()
////{
////    for(auto name : m_paramQualifiers){
////        auto condition = IHttpParameterRestrictManage::instance()->getRestrict(name);
////        if(condition == nullptr){
////            IHttpControllerAbort::abortParamRestrictNotExist();
////        }
////        restricts.append(condition);
////    }
////}

//void IArgumentTypeDetail::checkContentPositionMustBeIStringView()
//{
//    if(position == Position::Content && typeName != "IStringView"){
//        IHttpControllerAbort::abortParamPositionContentMustBeIStringViewType();
//    }
//}

//void IArgumentTypeDetail::checkBareResponseOrConstResponseRef()
//{
//    if(typeName == "IResponse"){
//        QString tip = "function at: " + m_methodSignature;
//        IHttpControllerAbort::abortParamBareResponseOrConstResponseRef(tip, $ISourceLocation);
//    }
//}

//void IArgumentTypeDetail::checkResponseAndRequestWithoutDecorators()
//{
////    if(typeName.startsWith("IRequest") || typeName.startsWith("IResponse")){
////        if(position != Position::Auto || !restricts.isEmpty()){
////            QString tip = "function at: " + m_methodSignature;
////            IHttpControllerAbort::abortParamBuiltInTypeCanNotBeDecorated(tip, $ISourceLocation);
////        }
////    }
//}

//void IArgumentTypeDetail::checkMethodSupportedParamArgType()
//{
//    static const QVector<QMetaType::Type> allowType = {
//        QMetaType::Bool,
//        QMetaType::Short,
//        QMetaType::UShort,
//        QMetaType::Int,
//        QMetaType::UInt,
//        QMetaType::Long,
//        QMetaType::ULong,
//        QMetaType::LongLong,
//        QMetaType::ULongLong,
//        QMetaType::Float,
//        QMetaType::Double,

//        QMetaType::QString,
//        QMetaType::QByteArray,

//        QMetaType::QJsonArray,
//        QMetaType::QJsonObject,
//        QMetaType::QJsonValue,
//    };

//    if(typeId >= QMetaType::User){
//        if(isEmbendedType()
//            || isDefinedType()
//            || IBeanTypeManage::instance()->isBeanIdExist(typeId)){
//            qFatal("error exist");
////                IHttpControllerAbort::abortcontroller_check_param_Type_has_unsupported_user_defined_type( QString("At Function: ").append(node.methodNode.signature)
////                                                                                                          .append(" At Param: ").append(typeName), $ISourceLocation);
//        }
//    } else{
//        if(!allowType.contains((QMetaType::Type)typeId)){
//            qFatal("error exist");
////                IHttpControllerAbort::abortcontroller_check_param_Type_has_unsupported_inner_type(QString("At Function: ").append(node.methodNode.signature)
////                                                                                                  .append(" At Param: ").append(typeName), $ISourceLocation);
//        }
//    }
//}

//void IArgumentTypeDetail::checkMethodBodyContentArgs()
//{
////        const auto& typeNames = node.methodNode.parameterTypeNames;
////        auto index = typeNames.indexOf("QJsonValue&");
////        if(index != -1){
////            const auto& paramNames = node.methodNode.parameterNames;
////            auto name = paramNames[index];
////            if(!name.endsWith("_content")){
////                QString info = "QJsonValue& can`t be used except in $Body expression\n"
////                               "at Function : " + node.methodNode.functionName;
////                qFatal(info.toUtf8());
////            }
////        }
//}

//void IArgumentTypeDetail::checkMethodParamterWithSuffixProper()
//{
////    const auto& argNodes = node.methodNode.argumentNodes;

////    // get 中不能调用 body 的参数。
////    if(node.httpMethod == IHttpMethod::GET){
////        for(const IArgumentTypeNode& param : argNodes){
////            if(param.name.endsWith("_body") || param.name.endsWith("_content")){
////                IHttpControllerAbort::abortcontroller_method_get_but_want_body_content(QString("At Function: ").append(node.methodNode.signature).append(" Parameter: ").append(param.name), $ISourceLocation);
////            }
////        }
////    }
//}

//// TODO: 这两个类型没有校验
//bool IArgumentTypeDetail::isDefinedType()
//{
//    static const QStringList specialExternalTypes = {
//        "IStringView",  "IJson"
//    };

//    return specialExternalTypes.contains(typeName);
//}

//bool IArgumentTypeDetail::isEmbendedType()
//{
//    static const QStringList s_embendedType = {
//        "IRequest",     "IRequest&",
//        "IResponse",    "IResponse&",
//        "IMultiPart",   "IMultiPart&",
//        "ICookieJar",   "ICookieJar&",
//        "ICookiePart",  "ICookiePart&"
//        "ISessionJar",  "ISessionJar&",
//        "IHeaderJar",   "IHeaderJar&",
//    };
//    return s_embendedType.contains(typeName);
//}

namespace ISpawnUtil {

template<>
IArgumentType construct(int paramTypeId, const char* paramTypeName, const char* paramName, QByteArray signature)
{
    return IArgumentTypeDetail(paramTypeId, paramTypeName, paramName, signature);
}

template<>
IArgumentType construct(int paramTypeId, QByteArray paramTypeName, QByteArray paramName, QByteArray signature)
{
    return IArgumentTypeDetail(paramTypeId, paramTypeName, paramName, signature);
}

template<>
IArgumentType construct(int paramTypeId, QString paramTypeName, QString paramName, QByteArray signature)
{
    return IArgumentTypeDetail(paramTypeId, paramTypeName, paramName, signature);
}
}

$PackageWebCoreEnd
