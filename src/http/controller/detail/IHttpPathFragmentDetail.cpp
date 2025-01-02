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

IWebCore::IHttpPathFragmentDetail::IHttpPathFragmentDetail(const QString &fragment)
{
    IHttpPathFragment::m_fragment = fragment;
    using FunType = bool (IHttpPathFragmentDetail::*)(const QString&);
    static const FunType funs[] = {
        &IHttpPathFragmentDetail::evaluateTypeEmptyNode,
        &IHttpPathFragmentDetail::evaluateNameOnlyNode,
        &IHttpPathFragmentDetail::evaluateNameTypeNode,
        &IHttpPathFragmentDetail::evaluateRegTypeNode,
        &IHttpPathFragmentDetail::evaluatePlainText,
    };

    for(const auto& fun : funs){
        if(std::mem_fn(fun)(this, fragment) == true){
            return;
        }
    }
    auto info = fragment + " is not a valid expression, please check it";
    qFatal(info.toUtf8());
}

bool IHttpPathFragmentDetail::evaluatePlainText(const QString &nodeName)
{
    QRegularExpression regex("^(?:[A-Za-z0-9\\-._~!$&'()*+,;=:@]|%[0-9A-Fa-f]{2})*$");
    auto result = regex.match(nodeName);
    if(result.hasMatch()){
        this->m_type = IHttpPathFragment::TEXT;
        return true;
    }
    return false;
}

bool IHttpPathFragmentDetail::evaluateTypeEmptyNode(const QString &nodeName)
{
    QRegularExpression regTypeEmpty("^<(\\w*)>$");
    auto result = regTypeEmpty.match(nodeName);
    if(result.hasMatch()){
        this->m_type = IHttpPathFragment::FULL_MATCH;
        this->m_name = result.captured(1);
        return true;
    }
    return false;
}

bool IHttpPathFragmentDetail::evaluateNameOnlyNode(const QString &nodeName)
{
    QRegularExpression regTypeNameOnly("^<(\\w+)>$");    // <name>
    auto result = regTypeNameOnly.match(nodeName);
    if(result.hasMatch()){
        this->m_name = result.captured(1);
        this->m_type = IHttpPathFragment::FULL_MATCH;
        return true;
    }
    return false;
}

bool IHttpPathFragmentDetail::evaluateNameTypeNode(const QString &nodeName)
{
    QRegularExpression regex("^<(\\w*)\\|(\\w+)>$");  // <name|function>
    auto result = regex.match(nodeName);
    if(!result.hasMatch()){
        return false;
    }

    this->m_name = result.captured(1);
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

bool IHttpPathFragmentDetail::evaluateRegTypeNode(const QString &nodeName)
{
    QRegularExpression regex("^<(\\w*)\\|\\|(.+)>$");  // <name||reg>
    auto result = regex.match(nodeName);
    if(!result.hasMatch()){
        return false;
    }

    this->m_type = IHttpPathFragment::FUNCTION;
    this->m_name = result.captured(1);
    auto exp = result.captured(2);

    QRegularExpression regExp(exp);
    if(!regExp.isValid()){
        qFatal("expression not valid");
    }
    this->m_validator = [=](const QString value)->bool{
        return regExp.match(value).hasMatch();
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
