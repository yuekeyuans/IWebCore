﻿#include "IArgumentTypeDetail.h"
#include "core/util/ISpawnUtil.h"
#include "core/bean/IBeanTypeManage.h"
#include "http/controller/IHttpControllerAbort.h"
#include "http/IHttpManage.h"
#include "http/invalid/IHttpInternalErrorInvalid.h"
#include "http/net/IRequest.h"
#include "http/net/IResponse.h"
#include "http/net/ICookieJar.h"
#include "http/net/ISessionJar.h"
#include "http/net/IMultiPartJar.h"
#include "http/net/IHeaderJar.h"
#include "http/net/impl/IRequestImpl.h"

$PackageWebCoreBegin

IArgumentTypeDetail::IArgumentTypeDetail(int typeId, QByteArray paramTypeName, QByteArray nameRaw)
    : IArgumentType()
{
    m_typeId = QMetaType::Type(typeId);
    m_typeName = std::move(paramTypeName);
    m_nameRaw = std::move(nameRaw);

    if(m_nameRaw.isEmpty()){
        qFatal("Name should not be empty");
    }

    resolveName();
    createBasicType();
    createPartType();
}

void IArgumentTypeDetail::resolveName()
{
    static const QVector<IString> PREFIXES = {
        "Auto", "Path", "Query", "Header", "Cookie", "Session", "Form", "Json"
    };
    IStringViewList args = m_nameRaw.split("_$");
    m_name = args.first();
    args.pop_front();

    for(IStringView arg : args){
        if(arg.startWith("Optional")){
            if(m_optional == true){
                qFatal("two more optional");
            }
            m_optional = true;
            continue;
        }

        auto index = PREFIXES.indexOf(arg);
        if(index > 0){
            if(m_position > 0){
                qFatal("two more restrict");
            }
            m_position = Position(index);
        }
    }
}

bool IArgumentTypeDetail::createBasicType()
{
    static QList<decltype(&IArgumentTypeDetail::createRequestType)> funs = {
        &IArgumentTypeDetail::createRequestType,
        &IArgumentTypeDetail::createResponseType,
        &IArgumentTypeDetail::createMultiPartJarType,
        &IArgumentTypeDetail::createCookieJarType,
        &IArgumentTypeDetail::createSessionJarType,
        &IArgumentTypeDetail::createHeaderJarType,
    };

    if(this->m_typeId != QMetaType::UnknownType){
        return false;
    }
    if(m_optional){
        qFatal("optional can not be exist here");
    }
    if(m_position != Position::Auto){
        qFatal("position should be empty");
    }
    for(auto fun : funs){
        std::mem_fn(fun)(this);
        if(this->m_createFun){
            return true;
        }
    }
}

void IArgumentTypeDetail::createRequestType()
{
    static const auto types = makeTypes("IRequest");
    if(types.contains(this->m_typeName)){
        this->m_createFun = [](IRequest& request)->void*{
            return &request;
        };
    }
}

void IArgumentTypeDetail::createResponseType()
{
    static const auto types = makeTypes("IResponse");
    if(types.contains(this->m_typeName)){
        this->m_createFun = [](IRequest& request)->void*{
            return new IResponse(request);
        };
        this->m_destroyFun = [](void* ptr){
            delete static_cast<IResponse*>(ptr);
        };
    }
}

void IArgumentTypeDetail::createMultiPartJarType()
{
    static const auto types = makeTypes("IMultiPartJar");
    if(types.contains(this->m_typeName)){
        this->m_createFun = [](IRequest& request)->void*{
            return &(request.impl().m_multiPartJar);
        };
    }
}

void IArgumentTypeDetail::createSessionJarType()
{
    static const auto types = makeTypes("ISessionJar");
    if(types.contains(this->m_typeName)){
        this->m_createFun = [](IRequest& request)->void*{
            return &(request.impl().m_sessionJar);
        };
    }
}

void IArgumentTypeDetail::createCookieJarType()
{
    static const auto types = makeTypes("ICookieJar");
    if(types.contains(this->m_typeName)){
        this->m_createFun = [](IRequest& request)->void*{
            return &(request.impl().m_cookieJar);
        };
    }
}

void IArgumentTypeDetail::createHeaderJarType()
{
    static const auto types = makeTypes("IHeaderJar");
    if(types.contains(this->m_typeName)){
        this->m_createFun = [](IRequest& request)->void*{
            return &(request.impl().m_headerJar);
        };
    }
}

bool IArgumentTypeDetail::createPartType()
{
    if(this->m_typeId != QMetaType::UnknownType){
        return false;
    }
    static QList<decltype(&IArgumentTypeDetail::createRequestType)> funs = {
        &IArgumentTypeDetail::createMultiPartType,
        &IArgumentTypeDetail::createCookiePartType,
    };
    for(auto fun : funs){
        std::mem_fn(fun)(this);
        if(this->m_createFun){
            return true;
        }
    }
    return false;
}

void IArgumentTypeDetail::createMultiPartType()
{
    static const auto types = makeTypes("IMultiPart");
    if(types.contains(this->m_typeName)){
        if(m_position != Position::Auto){
            qFatal("position should be empty");
        }

        bool m_optional = this->m_optional;         // weired!!!
        IString m_name = this->m_name;
        this->m_createFun = [m_optional, m_name](IRequest& request) -> void*{
            if(!request.bodyContentType().startWith(IHttpMimeUtil::toString(IHttpMime::MULTIPART_FORM_DATA))){ // TODO: force little case
                request.setInvalid(IHttpInternalErrorInvalid("not multitype type"));
                return nullptr;
            }else{
                const auto& value = request.multiPartJar().getMultiPart(m_name);
                if(!m_optional && (&value == &IMultiPart::Empty)){
                    request.setInvalid(IHttpInternalErrorInvalid("multitype not optional"));
                    return nullptr;
                }
                return static_cast<void*>(const_cast<IMultiPart*>(&value));
            }
        };
    }
}

void IArgumentTypeDetail::createCookiePartType()
{

}

QVector<IString> IArgumentTypeDetail::makeTypes(const std::string &name)
{
    QVector<IString> names;
    names.append(name);
    names.append((name + "&"));
    names.append((std::string($PackageWebCoreName) + "::" + name));
    names.append((std::string($PackageWebCoreName) + "::" + name + "&"));

    return names;
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
    IArgumentType construct(int paramTypeId, QByteArray paramTypeName, QByteArray paramName)
    {
        return IArgumentTypeDetail(paramTypeId, std::move(paramTypeName), std::move(paramName));
    }
}

$PackageWebCoreEnd
