#include "IParamNode.h"
#include "http/base/IHttpParameterRestrictManage.h"
#include "http/base/IHttpParameterRestrictInterface.h"
#include "http/controller/IHttpControllerAbort.h"
#include "http/controller/IHttpManage.h"

$PackageWebCoreBegin

// TODO: 这里 Nullable/NotNull 替换为Optional, 具体的参数见文档
struct IParamNodeDetail : public IParamNode
{
public:
    IParamNodeDetail(int paramTypeId, QString paramTypeName, QString paramName);

private:
    void checkParamType();
    void checkParamNameEmpty();
    void checkParamDuplicated();
    void checkAndSetParamPosition();
    void checkAndSetParamOptional();
    void checkAndSetParamRestrictions();
    void checkContentPositionMustBeIStringView();

private:
    inline static const QStringList QualifierNames = {
        "mixed", "param", "url", "header", "body", "content",  "cookie", "session"
    };
    inline static const QString NullableName = "nullable";
    inline static const QString NotnullName = "notnull";
    QStringList m_paramQualifiers;
};

inline IParamNodeDetail::IParamNodeDetail(int paramTypeId_, QString paramTypeName_, QString name_)
{
    paramTypeId = paramTypeId_;
    paramTypeName = paramTypeName_;
    paramNameRaw = name_;
    auto args = paramNameRaw.split("_$");
    paramName = args.first();
    paramNameView = IGlobalStringViewStash(paramName);
    args.pop_front();
    m_paramQualifiers = args;

    using CheckType = void(IParamNodeDetail::*)();
    QList<CheckType> checks = {
        &IParamNodeDetail::checkParamType,
        &IParamNodeDetail::checkParamNameEmpty,
        &IParamNodeDetail::checkParamDuplicated,
        &IParamNodeDetail::checkAndSetParamPosition,
        &IParamNodeDetail::checkAndSetParamOptional,
        &IParamNodeDetail::checkContentPositionMustBeIStringView
    };

    for(auto check : checks){
        std::bind(check, this)();
    }
}

inline void IParamNodeDetail::checkParamType()
{
    if(paramTypeId == QMetaType::UnknownType){
        IHttpControllerAbort::abortParamErrorOfUnknowType();
    }
}

inline void IParamNodeDetail::checkParamNameEmpty()
{
    if(paramName.trimmed().isEmpty()){
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
    if(position == Position::Content && paramTypeName != "IStringView"){
        IHttpControllerAbort::abortParamPositionContentMustBeIStringViewType();
    }
}

namespace ISpawnUtil {

    template<>
    IParamNode construct(int paramTypeId, const char* paramTypeName, const char* paramName)
    {
        return IParamNodeDetail(paramTypeId, paramTypeName, paramName);
    }

    template<>
    IParamNode construct(int paramTypeId, QByteArray paramTypeName, QByteArray paramName)
    {
        return IParamNodeDetail(paramTypeId, paramTypeName, paramName);
    }

    template<>
    IParamNode construct(int paramTypeId, QString paramTypeName, QString paramName)
    {
        return IParamNodeDetail(paramTypeId, paramTypeName, paramName);
    }
}

$PackageWebCoreEnd
