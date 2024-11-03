#include "IParameterNode.h"
#include "core/util/ISpawnUtil.h"
#include "http/base/IHttpParameterRestrictManage.h"
#include "http/base/IHttpParameterRestrictInterface.h"
#include "http/controller/IHttpControllerAbort.h"
#include "http/IHttpManage.h"

$PackageWebCoreBegin

// TODO: 这里 Nullable/NotNull 替换为Optional, 具体的参数见文档
struct IParamNodeDetail : public IParameterNode
{
public:
    IParamNodeDetail(int typeId, QString typeName, QString name, QString m_methodSignature);

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

private:
    inline static const QStringList QualifierNames = {
        "auto", "query", "path", "header", "body", "content",  "cookie", "session"
    };
    inline static const QString NullableName = "nullable";
    inline static const QString NotnullName = "notnull";
    QStringList m_paramQualifiers;
    QString m_methodSignature;
};

inline IParamNodeDetail::IParamNodeDetail(int paramTypeId_, QString paramTypeName_, QString name_, QString methodSignature_)
{
    typeId = paramTypeId_;
    typeName = paramTypeName_;
    nameRaw = name_;
    m_methodSignature = methodSignature_;
    auto args = nameRaw.split("_$");
    name = args.first();
    args.pop_front();
    m_paramQualifiers = args;

    using CheckType = void(IParamNodeDetail::*)();
    QList<CheckType> checks = {
        &IParamNodeDetail::checkParamType,
        &IParamNodeDetail::checkParamNameEmpty,
        &IParamNodeDetail::checkParamDuplicated,
        &IParamNodeDetail::checkAndSetParamPosition,
        &IParamNodeDetail::checkAndSetParamOptional,
        &IParamNodeDetail::checkContentPositionMustBeIStringView,
        &IParamNodeDetail::checkBareResponseOrConstResponseRef,
        &IParamNodeDetail::checkResponseAndRequestWithoutDecorators,
    };

    for(auto check : checks){
        std::bind(check, this)();
    }
}

inline void IParamNodeDetail::checkParamType()
{
    if(typeId == QMetaType::UnknownType){
        IHttpControllerAbort::abortParamErrorOfUnknowType();
    }
}

inline void IParamNodeDetail::checkParamNameEmpty()
{
    if(name.trimmed().isEmpty()){
        IHttpControllerAbort::abortParamNameEmpty();
    }
}

inline void IParamNodeDetail::checkParamDuplicated()
{
    if(m_paramQualifiers.length() != m_paramQualifiers.toSet().size()){
        IHttpControllerAbort::abortParamQualifersDuplicated();
    }
}

inline void IParamNodeDetail::checkAndSetParamPosition()
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

inline void IParamNodeDetail::checkAndSetParamOptional()
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

inline void IParamNodeDetail::checkAndSetParamRestrictions()
{
    for(auto name : m_paramQualifiers){
        auto condition = IHttpParameterRestrictManage::instance()->getRestrict(name);
        if(condition == nullptr){
            IHttpControllerAbort::abortParamRestrictNotExist();
        }
        restricts.append(condition);
    }
}

inline void IParamNodeDetail::checkContentPositionMustBeIStringView()
{
    if(position == Position::Content && typeName != "IStringView"){
        IHttpControllerAbort::abortParamPositionContentMustBeIStringViewType();
    }
}

void IParamNodeDetail::checkBareResponseOrConstResponseRef()
{
    if(typeName == "IResponse"){
        QString tip = "function at: " + m_methodSignature;
        IHttpControllerAbort::abortParamBareResponseOrConstResponseRef(tip, $ISourceLocation);
    }
}

void IParamNodeDetail::checkResponseAndRequestWithoutDecorators()
{
    if(typeName.startsWith("IRequest") || typeName.startsWith("IResponse")){
        if(position != Position::Auto || !restricts.isEmpty()){
            QString tip = "function at: " + m_methodSignature;
            IHttpControllerAbort::abortParamBuiltInTypeCanNotBeDecorated(tip, $ISourceLocation);
        }
    }
}

namespace ISpawnUtil {

    template<>
    IParameterNode construct(int paramTypeId, const char* paramTypeName, const char* paramName, QByteArray signature)
    {
        return IParamNodeDetail(paramTypeId, paramTypeName, paramName, signature);
    }

    template<>
    IParameterNode construct(int paramTypeId, QByteArray paramTypeName, QByteArray paramName, QByteArray signature)
    {
        return IParamNodeDetail(paramTypeId, paramTypeName, paramName, signature);
    }

    template<>
    IParameterNode construct(int paramTypeId, QString paramTypeName, QString paramName, QByteArray signature)
    {
        return IParamNodeDetail(paramTypeId, paramTypeName, paramName, signature);
    }
}

$PackageWebCoreEnd
