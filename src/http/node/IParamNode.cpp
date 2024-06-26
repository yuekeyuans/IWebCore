#include "IParamNode.h"
#include "core/assert/IAbortInterface.h"
#include "http/node/IHttpParameterRestrictManage.h"
#include "http/node/IHttpParameterRestrictInterface.h"
#include "http/controller/IHttpManage.h"

$PackageWebCoreBegin


class IParamNodeAbort : public IAbortInterface<IParamNodeAbort>
{
public:
    $AsAbort(
        Error1,
        Error2
    )
public:
    virtual QMap<int, QString> getAbortInfo() const {
        return {
            {Error1, "hello"},
            {Error2, "world"}
        };
    }

};

namespace detail {
    static const QStringList qualifierNames = {
        "mixed", "param", "url", "header", "body", "content",  "cookie", "session"
    };
    static const QString nullableName = "nullable";
    static const QString notnullName = "notnull";
}

IParamNode::IParamNode(int paramTypeId, QString paramTypeName, QString name)
    : paramTypeId(paramTypeId), paramTypeName(paramTypeName)
{
    IParamNodeAbort::abortError1();
    auto args = name.split("_$");
    paramName = args.first();
    paramNameView = IHttpManage::instance()->stash(paramName.toUtf8());
    args.pop_front();
    m_paramQualifiers = args;

    using CheckType = void(IParamNode::*)();
    QList<CheckType> checks = {
        &IParamNode::checkParamType,
        &IParamNode::checkParamNameEmpty,
        &IParamNode::checkParamDuplicated,
        &IParamNode::checkAndSetParamPosition,
        &IParamNode::checkAndSetParamOptional,
        &IParamNode::checkContentPositionMustBeIStringView
    };

    for(auto check : checks){
        std::bind(check, this)();
        if(!m_error.isEmpty()){
            return;
        }
    }
}

QString IParamNode::getError()
{
    return m_error;
}

void IParamNode::checkParamType()
{
    if(paramTypeId == QMetaType::UnknownType){
        m_error = "ParamErrorOfUnknowType";
    }
}

void IParamNode::checkParamNameEmpty()
{
    if(paramName.trimmed().isEmpty()){
        m_error = "ParamNameEmpty";
    }
}

void IParamNode::checkParamDuplicated()
{
    if(m_paramQualifiers.length() != m_paramQualifiers.toSet().size()){
        m_error = "ParamQualifersDuplicated";
    }
}

void IParamNode::checkAndSetParamPosition()
{
    bool exist{false};
    for(auto name : detail::qualifierNames){
        if(m_paramQualifiers.contains(name)){
            if(exist){
                m_error = "ParamPositionDuplicated";
                return;
            }
            position = Position(detail::qualifierNames.indexOf(name));
            m_paramQualifiers.removeOne(name);
            exist = true;
        }
    }
}

void IParamNode::checkAndSetParamOptional()
{
    bool exist{false};
    if(m_paramQualifiers.contains(detail::nullableName)){
        optional = true;
        m_paramQualifiers.removeAll(detail::nullableName);
        exist = true;
    }
    if(m_paramQualifiers.contains(detail::notnullName)){
        if(exist){
            m_error = "ParamNullableConflict";
            return;
        }
        optional = false;
        m_paramQualifiers.removeAll(detail::notnullName);
    }
}

void IParamNode::checkAndSetParamRestrictions()
{
    for(auto name : m_paramQualifiers){
        auto condition = IHttpParameterRestrictManage::instance()->getRestrict(name);
        if(condition == nullptr){
            m_error = "ParamRestrictNotExist";
            return;
        }
        restricts.append(condition);
    }
}

void IParamNode::checkContentPositionMustBeIStringView()
{
    if(position == Position::Content && paramTypeName != "IStringView"){
        m_error = "ParamPositionContentMustBeIStringViewType";
    }
}


$PackageWebCoreEnd
