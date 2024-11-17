#include "IArgumentTypeNode.h"
#include "core/util/ISpawnUtil.h"
#include "core/bean/IBeanTypeManage.h"
#include "http/base/IHttpParameterRestrictManage.h"
#include "http/base/IHttpParameterRestrictInterface.h"
#include "http/controller/IHttpControllerAbort.h"
#include "http/IHttpManage.h"

$PackageWebCoreBegin

// TODO: 这里 Nullable/NotNull 替换为Optional, 具体的参数见文档
struct IArgumentTypeNodeDetail : public IArgumentTypeNode
{
public:
    IArgumentTypeNodeDetail(int typeId, QString typeName, QString name, QString m_methodSignature);

private:
    void checkParamType();
    void checkParamNameEmpty();
    void checkParamDuplicated();
    void checkAndSetParamPosition();
    void checkAndSetParamOptional();
    void checkAndSetParamRestrictions();
    void checkContentPositionMustBeIStringView();
    void checkBareResponseOrConstResponseRef(); // IResponse or const IResponse& is not allowed
    void checkResponseAndRequestWithoutDecorators();    // IRequest and Response can not be decorated

private: // TODO: check
    void checkMethodSupportedParamArgType();
    void checkMethodBodyContentArgs();
    void checkMethodParamterWithSuffixProper();
    bool isDefinedType();
    bool isEmbendedType();

private:
    inline static const QStringList QualifierNames = {
        "auto", "query", "path", "header", "body", "content",  "cookie", "session"
    };
    inline static const QString NullableName = "nullable";
    inline static const QString NotnullName = "notnull";
    QStringList m_paramQualifiers;
    QString m_methodSignature;
};

inline IArgumentTypeNodeDetail::IArgumentTypeNodeDetail(int paramTypeId_, QString paramTypeName_, QString name_, QString methodSignature_)
{
    typeId = (QMetaType::Type)paramTypeId_;
    typeName = paramTypeName_;
    nameRaw = name_;
    m_methodSignature = methodSignature_;

    auto args = nameRaw.split("_$");
    name = args.first();
    args.pop_front();
    m_paramQualifiers = args;

    using CheckType = void(IArgumentTypeNodeDetail::*)();
    QList<CheckType> checks = {
        &IArgumentTypeNodeDetail::checkParamType,
        &IArgumentTypeNodeDetail::checkParamNameEmpty,
        &IArgumentTypeNodeDetail::checkParamDuplicated,
        &IArgumentTypeNodeDetail::checkAndSetParamPosition,
        &IArgumentTypeNodeDetail::checkAndSetParamOptional,
        &IArgumentTypeNodeDetail::checkContentPositionMustBeIStringView,
        &IArgumentTypeNodeDetail::checkBareResponseOrConstResponseRef,
        &IArgumentTypeNodeDetail::checkResponseAndRequestWithoutDecorators,
    };

    for(auto check : checks){
        std::bind(check, this)();
    }
}

inline void IArgumentTypeNodeDetail::checkParamType()
{
    if(typeId == QMetaType::UnknownType){
        IHttpControllerAbort::abortParamErrorOfUnknowType();
    }
}

inline void IArgumentTypeNodeDetail::checkParamNameEmpty()
{
    if(!isEmbendedType() && name.trimmed().isEmpty()){
        IHttpControllerAbort::abortParamNameEmpty();
    }
}

inline void IArgumentTypeNodeDetail::checkParamDuplicated()
{
    if(m_paramQualifiers.length() != m_paramQualifiers.toSet().size()){
        IHttpControllerAbort::abortParamQualifersDuplicated();
    }
}

inline void IArgumentTypeNodeDetail::checkAndSetParamPosition()
{
    bool exist{false};
    for(auto name : QualifierNames){
        if(m_paramQualifiers.contains(name)){
            if(exist){
                IHttpControllerAbort::abortParamPositionDuplicated();
            }
            position = Position(QualifierNames.indexOf(name));
            m_paramQualifiers.removeOne(name);
            exist = true;
        }
    }
}

inline void IArgumentTypeNodeDetail::checkAndSetParamOptional()
{
    bool exist{false};
    if(m_paramQualifiers.contains(NullableName)){
        optional = true;
        m_paramQualifiers.removeAll(NullableName);
        exist = true;
    }
    if(m_paramQualifiers.contains(NotnullName)){
        if(exist){
            IHttpControllerAbort::abortParamNullableConflict();
        }
        optional = false;
        m_paramQualifiers.removeAll(NotnullName);
    }
}

inline void IArgumentTypeNodeDetail::checkAndSetParamRestrictions()
{
    for(auto name : m_paramQualifiers){
        auto condition = IHttpParameterRestrictManage::instance()->getRestrict(name);
        if(condition == nullptr){
            IHttpControllerAbort::abortParamRestrictNotExist();
        }
        restricts.append(condition);
    }
}

inline void IArgumentTypeNodeDetail::checkContentPositionMustBeIStringView()
{
    if(position == Position::Content && typeName != "IStringView"){
        IHttpControllerAbort::abortParamPositionContentMustBeIStringViewType();
    }
}

void IArgumentTypeNodeDetail::checkBareResponseOrConstResponseRef()
{
    if(typeName == "IResponse"){
        QString tip = "function at: " + m_methodSignature;
        IHttpControllerAbort::abortParamBareResponseOrConstResponseRef(tip, $ISourceLocation);
    }
}

void IArgumentTypeNodeDetail::checkResponseAndRequestWithoutDecorators()
{
    if(typeName.startsWith("IRequest") || typeName.startsWith("IResponse")){
        if(position != Position::Auto || !restricts.isEmpty()){
            QString tip = "function at: " + m_methodSignature;
            IHttpControllerAbort::abortParamBuiltInTypeCanNotBeDecorated(tip, $ISourceLocation);
        }
    }
}

void IArgumentTypeNodeDetail::checkMethodSupportedParamArgType()
{
    static const QVector<QMetaType::Type> allowType = {
        QMetaType::Bool,
        QMetaType::Short,
        QMetaType::UShort,
        QMetaType::Int,
        QMetaType::UInt,
        QMetaType::Long,
        QMetaType::ULong,
        QMetaType::LongLong,
        QMetaType::ULongLong,
        QMetaType::Float,
        QMetaType::Double,

        QMetaType::QString,
        QMetaType::QByteArray,

        QMetaType::QJsonArray,
        QMetaType::QJsonObject,
        QMetaType::QJsonValue,
    };

    if(typeId >= QMetaType::User){
        if(isEmbendedType()
            || isDefinedType()
            || IBeanTypeManage::instance()->isBeanIdExist(typeId)){
            qFatal("error exist");
//                IHttpControllerAbort::abortcontroller_check_param_Type_has_unsupported_user_defined_type( QString("At Function: ").append(node.methodNode.signature)
//                                                                                                          .append(" At Param: ").append(typeName), $ISourceLocation);
        }
    } else{
        if(!allowType.contains((QMetaType::Type)typeId)){
            qFatal("error exist");
//                IHttpControllerAbort::abortcontroller_check_param_Type_has_unsupported_inner_type(QString("At Function: ").append(node.methodNode.signature)
//                                                                                                  .append(" At Param: ").append(typeName), $ISourceLocation);
        }
    }
}

void IArgumentTypeNodeDetail::checkMethodBodyContentArgs()
{
//        const auto& typeNames = node.methodNode.parameterTypeNames;
//        auto index = typeNames.indexOf("QJsonValue&");
//        if(index != -1){
//            const auto& paramNames = node.methodNode.parameterNames;
//            auto name = paramNames[index];
//            if(!name.endsWith("_content")){
//                QString info = "QJsonValue& can`t be used except in $Body expression\n"
//                               "at Function : " + node.methodNode.functionName;
//                qFatal(info.toUtf8());
//            }
//        }
}

void IArgumentTypeNodeDetail::checkMethodParamterWithSuffixProper()
{
//    const auto& argNodes = node.methodNode.argumentNodes;

//    // get 中不能调用 body 的参数。
//    if(node.httpMethod == IHttpMethod::GET){
//        for(const IArgumentTypeNode& param : argNodes){
//            if(param.name.endsWith("_body") || param.name.endsWith("_content")){
//                IHttpControllerAbort::abortcontroller_method_get_but_want_body_content(QString("At Function: ").append(node.methodNode.signature).append(" Parameter: ").append(param.name), $ISourceLocation);
//            }
//        }
//    }
}

// TODO: 这两个类型没有校验
bool IArgumentTypeNodeDetail::isDefinedType()
{
    static const QStringList specialExternalTypes = {
        "IStringView",  "IJson"
    };

    return specialExternalTypes.contains(typeName);
}

bool IArgumentTypeNodeDetail::isEmbendedType()
{
    static const QStringList s_embendedType = {
        "IRequest",     "IRequest&",
        "IResponse",    "IResponse&",
        "IMultiPart",   "IMultiPart&",
        "ICookieJar",   "ICookieJar&",
        "ICookiePart",  "ICookiePart&"
        "ISessionJar",  "ISessionJar&",
        "IHeaderJar",   "IHeaderJar&",
    };
    return s_embendedType.contains(typeName);
}

namespace ISpawnUtil {

template<>
IArgumentTypeNode construct(int paramTypeId, const char* paramTypeName, const char* paramName, QByteArray signature)
{
    return IArgumentTypeNodeDetail(paramTypeId, paramTypeName, paramName, signature);
}

template<>
IArgumentTypeNode construct(int paramTypeId, QByteArray paramTypeName, QByteArray paramName, QByteArray signature)
{
    return IArgumentTypeNodeDetail(paramTypeId, paramTypeName, paramName, signature);
}

template<>
IArgumentTypeNode construct(int paramTypeId, QString paramTypeName, QString paramName, QByteArray signature)
{
    return IArgumentTypeNodeDetail(paramTypeId, paramTypeName, paramName, signature);
}
}

void *IArgumentTypeNode::create(IRequest &) const
{
    return nullptr;
}

void IArgumentTypeNode::destory(void *ptr) const
{
    // do nothing here
}

$PackageWebCoreEnd
