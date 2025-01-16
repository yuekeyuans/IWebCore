#include "IHttpPathFragmentDetail.h"
#include "core/util/ISpawnUtil.h"
#include "http/IHttpManage.h"

$PackageWebCoreBegin

/*
 *  <>
 *  <name>
 *  <name|function>
 *  <|function>
 *  <name||reg>
 *  <||reg>
 *  plainText
 */

IWebCore::IHttpPathFragmentDetail::IHttpPathFragmentDetail(const QString& fragment)
{
    IHttpPathFragment::m_fragment = fragment.toUtf8();
    using FunType = bool (IHttpPathFragmentDetail::*)();
    static const FunType funs[] = {
        &IHttpPathFragmentDetail::evaluateTypeEmptyNode,
        &IHttpPathFragmentDetail::evaluateNameOnlyNode,
        &IHttpPathFragmentDetail::evaluateNameTypeNode,
        &IHttpPathFragmentDetail::evaluateRegTypeNode,
        &IHttpPathFragmentDetail::evaluatePlainText,
    };

    for(const auto& fun : funs){
        if(std::invoke(fun, this) == true){
            return;
        }
    }
    QString info = m_fragment.toQString() + " is not a valid expression, please check it";
    qFatal(info.toUtf8());
}

bool IHttpPathFragmentDetail::evaluatePlainText()
{
    QRegularExpression regex("^(?:[A-Za-z0-9\\-._~!$&'()*+,;=:@]|%[0-9A-Fa-f]{2})*$");
    auto result = regex.match(m_fragment.toQString());
    if(result.hasMatch()){
        this->m_type = IHttpPathFragment::TEXT;
        return true;
    }
    return false;
}

bool IHttpPathFragmentDetail::evaluateTypeEmptyNode()
{
    QRegularExpression regTypeEmpty("^<(\\w*)>$");
    auto result = regTypeEmpty.match(m_fragment.toQString());
    if(result.hasMatch()){
        this->m_type = IHttpPathFragment::FULL_MATCH;
        this->m_name = result.captured(1).toStdString();
        return true;
    }
    return false;
}

bool IHttpPathFragmentDetail::evaluateNameOnlyNode()
{
    QRegularExpression regTypeNameOnly("^<(\\w+)>$");    // <name>
    auto result = regTypeNameOnly.match(m_fragment.toQString());
    if(result.hasMatch()){
        this->m_name = result.captured(1).toStdString();
        this->m_type = IHttpPathFragment::FULL_MATCH;
        return true;
    }
    return false;
}

bool IHttpPathFragmentDetail::evaluateNameTypeNode()
{
    QRegularExpression regex("^<(\\w*)\\|(\\w+)>$");  // <name|function>
    auto result = regex.match(m_fragment.toQString());
    if(!result.hasMatch()){
        return false;
    }

    this->m_name = result.captured(1).toStdString();
    auto valueType = result.captured(2);
    if(valueType.isEmpty()){
        qFatal("no capture function name found");
    }

    auto fun = IHttpManage::instance()->queryPathFunValidator(valueType);
    if(fun != nullptr){
        this->m_validator = fun;
        this->m_type = IHttpPathFragment::FUNCTION;
        return true;
    }else{
        qFatal("not supported path function");
    }
    return false;
}

bool IHttpPathFragmentDetail::evaluateRegTypeNode()
{
    QRegularExpression regex("^<(\\w*)\\|\\|(.+)>$");  // <name||reg>
    auto result = regex.match(m_fragment.toQString());
    if(!result.hasMatch()){
        return false;
    }

    this->m_type = IHttpPathFragment::FUNCTION;
    this->m_name = result.captured(1).toStdString();
    auto exp = result.captured(2);

    QRegularExpression regExp(exp);
    if(!regExp.isValid()){
        qFatal("expression not valid");
    }
    this->m_validator = [=](IString value)->bool{
        return regExp.match(value.toQString()).hasMatch();
    };
    return true;
}

namespace ISpawnUtil
{
    template<>
    IHttpPathFragment construct(QString data)
    {
        return IHttpPathFragmentDetail(data);
    }
}

$PackageWebCoreEnd
