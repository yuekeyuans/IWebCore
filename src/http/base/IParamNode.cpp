#include "IParamNode.h"
#include "core/abort/IAbortInterface.h"
#include "http/base/IHttpParameterRestrictManage.h"
#include "http/base/IHttpParameterRestrictInterface.h"
#include "http/controller/IHttpManage.h"

$PackageWebCoreBegin

class IParamNodeAbort : public IAbortInterface<IParamNodeAbort>
{
    $AsAbort(
        ParamErrorOfUnknowType,
        ParamNameEmpty,
        ParamQualifersDuplicated,
        ParamPositionDuplicated,
        ParamNullableConflict,
        ParamRestrictNotExist,
        ParamPositionContentMustBeIStringViewType
    )

public:
    virtual QMap<int, QString> abortDescription() const final{
        return {
            {ParamErrorOfUnknowType, "request parameter use an unknown or unregistered or unsupported type"},
            {ParamNameEmpty, "request parameter name is empty"},
            {ParamQualifersDuplicated, "request parameter qualifiers duplicated, please check the annomacro and remove the duplicated annomacro"},
            {ParamPositionDuplicated, "request parameter position annomacro can only has at most one. please remove the extra position annomacro"},
            {ParamNullableConflict, "request parameter optional annomacro can only be $NotNull or $Nullable, both two can not be occurred at the same time"},
            {ParamRestrictNotExist, "request parameter has restriction annomacro that not registered in system, please check the annomacro"},
            {ParamPositionContentMustBeIStringViewType, "request parameter with $Content annomacro must use IStringView as its type"}
        };
    }
    virtual QString abortComment() final{
        return "This abort only occurred at resolving controller parameter";
    }
};

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

inline IParamNodeDetail::IParamNodeDetail(int paramTypeId, QString paramTypeName, QString name)
{
    paramTypeId = paramTypeId;
    paramTypeName = paramTypeName;
    auto args = name.split("_$");
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
        IParamNodeAbort::abortParamErrorOfUnknowType();
    }
}

inline void IParamNodeDetail::checkParamNameEmpty()
{
    if(paramName.trimmed().isEmpty()){
        IParamNodeAbort::abortParamNameEmpty();
    }
}

inline void IParamNodeDetail::checkParamDuplicated()
{
    if(m_paramQualifiers.length() != m_paramQualifiers.toSet().size()){
        IParamNodeAbort::abortParamQualifersDuplicated();
    }
}

inline void IParamNodeDetail::checkAndSetParamPosition()
{
    bool exist{false};
    for(auto name : QualifierNames){
        if(m_paramQualifiers.contains(name)){
            if(exist){
                IParamNodeAbort::abortParamPositionDuplicated();
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
            IParamNodeAbort::abortParamNullableConflict();
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
            IParamNodeAbort::abortParamRestrictNotExist();
        }
        restricts.append(condition);
    }
}

inline void IParamNodeDetail::checkContentPositionMustBeIStringView()
{
    if(position == Position::Content && paramTypeName != "IStringView"){
        IParamNodeAbort::abortParamPositionContentMustBeIStringViewType();
    }
}

IParamNode IParamNodeHelper::createParamNode(int paramTypeId, QString paramTypeName, QString paramName)
{
    return IParamNodeDetail(paramTypeId, paramTypeName, paramName);
}

$PackageWebCoreEnd
