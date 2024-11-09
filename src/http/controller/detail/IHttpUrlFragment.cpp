#include "IHttpUrlFragment.h"
#include "http/IHttpManage.h"
#include "core/util/ISpawnUtil.h"

$PackageWebCoreBegin

bool IHttpUrlFragment::isMatch(IStringView value) const
{
    return isMatch(value.toQString());
}

bool IHttpUrlFragment::isMatch(const QString &nodeName) const
{
    return false
            || type == IHttpUrlFragment::TEXT_MATCH && fragment == nodeName
            || type == IHttpUrlFragment::REGEXP_MATCH && regexpValidator.match(nodeName).hasMatch()
            || type == IHttpUrlFragment::FUNC_MATCH && funValidator(nodeName)
            || type == IHttpUrlFragment::FULL_MATCH;
}


struct IHttpUrlFragmentDetail : public IHttpUrlFragment
{
public:
    IHttpUrlFragmentDetail(const QString& fragment);

private:
    bool evaluatePlainText(const QString& nodeName);
    bool evaluateTypeEmptyNode(const QString &nodeName);
    bool evaluateNameOnlyNode(const QString &nodeName);
    bool evaluateNameTypeNode(const QString &nodeName);
    bool evaluateRegTypeNode(const QString &nodeName);
    bool evaluateUnMatchedNode(const QString &nodeName);
};

IHttpUrlFragmentDetail::IHttpUrlFragmentDetail(const QString &_fragment)
{
    using FunType = bool (IHttpUrlFragmentDetail::*)(const QString&);
    static FunType funs[] = {
        &IHttpUrlFragmentDetail::evaluateTypeEmptyNode,
        &IHttpUrlFragmentDetail::evaluateNameOnlyNode,
        &IHttpUrlFragmentDetail::evaluateNameTypeNode,
        &IHttpUrlFragmentDetail::evaluateRegTypeNode,
        &IHttpUrlFragmentDetail::evaluatePlainText,
        &IHttpUrlFragmentDetail::evaluateUnMatchedNode
    };

    fragment = _fragment;
    type = IHttpUrlFragment::REGEXP_MATCH;
    for(const auto& fun : funs){
        if(std::mem_fn(fun)(this, fragment) == true){
            break;
        }
    }
}

bool IHttpUrlFragmentDetail::evaluatePlainText(const QString &nodeName)
{
    static QRegularExpression plainTextType("^\\w+$");
    auto result = plainTextType.match(nodeName);
    if(result.hasMatch()){
        this->type = IHttpUrlFragment::TEXT_MATCH;
        return true;
    }
    return false;
}

bool IHttpUrlFragmentDetail::evaluateTypeEmptyNode(const QString &nodeName)
{
    static QRegularExpression regTypeEmpty("^<>$");
    auto result = regTypeEmpty.match(nodeName);
    if(result.hasMatch()){
        this->type = IHttpUrlFragment::FULL_MATCH;
        return true;
    }
    return false;
}

bool IHttpUrlFragmentDetail::evaluateNameOnlyNode(const QString &nodeName)
{
    static QRegularExpression regTypeNameOnly("^<(\\w+)>$");
    auto result = regTypeNameOnly.match(nodeName);
    if(result.hasMatch()){
        this->name = result.captured(1);
        this->type = IHttpUrlFragment::FULL_MATCH;
        return true;
    }
    return false;
}

bool IHttpUrlFragmentDetail::evaluateNameTypeNode(const QString &nodeName)
{
    static QRegularExpression regTypeNameValue("^<(\\w*):(\\w*)>$");
    auto result = regTypeNameValue.match(nodeName);
    if(!result.hasMatch()){
        return false;
    }

    this->name = result.captured(1);
    auto valueType = result.captured(2);
    if(!valueType.isEmpty()){
        auto express = IHttpManage::queryPathRegValidator(valueType);
        if(!express.isEmpty()){
            this->regexpValidator = QRegularExpression(express);
            this->type = IHttpUrlFragment::REGEXP_MATCH;
            return true;
        }

        auto fun = IHttpManage::queryPathFunValidator(valueType);
        if(fun != nullptr){
            this->funValidator = fun;
            this->type = IHttpUrlFragment::FUNC_MATCH;
            return true;
        }
    }else  {
        this->type = IHttpUrlFragment::FULL_MATCH;
        return true;
    }
    return false;
}

bool IHttpUrlFragmentDetail::evaluateRegTypeNode(const QString &nodeName)
{
    static QRegularExpression regTypeNameReg("^<(reg)?:(\\w*):(\\w*)>$");
    if(regTypeNameReg.match(nodeName).hasMatch()){
        auto result = regTypeNameReg.match(nodeName);
        this->type = IHttpUrlFragment::REGEXP_MATCH;
        this->name = result.captured(2);

        auto expression = result.captured(3);
        this->regexpValidator = QRegularExpression(expression);
        if(!this->regexpValidator.isValid()){
            QString info = nodeName + " has invalid regular expression, please check it";
            qFatal(info.toUtf8());
        }
        return true;
    }
    return false;
}

bool IHttpUrlFragmentDetail::evaluateUnMatchedNode(const QString &nodeName)
{
    auto info = nodeName + " is not a valid expression, please check it";
    qFatal(info.toUtf8());
    return true;
}


namespace ISpawnUtil
{
    template<>
    IHttpUrlFragment construct(QString data)
    {
        return IHttpUrlFragmentDetail(data);
    }
}

$PackageWebCoreEnd




