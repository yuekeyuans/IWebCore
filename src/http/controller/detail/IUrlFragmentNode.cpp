#include "IUrlFragmentNode.h"
#include "http/IHttpManage.h"

$PackageWebCoreBegin

// TODO: 重构
namespace detail
{
    struct IHttpRouteNodeDetail : public IUrlFragmentNode
    {
        IHttpRouteNodeDetail(const QString& _fragment)
        {
            using FunType = bool (IHttpRouteNodeDetail::*)(const QString&);
            static FunType funs[] = {
                &IHttpRouteNodeDetail::evaluateTypeEmptyNode,
                &IHttpRouteNodeDetail::evaluateNameOnlyNode,
                &IHttpRouteNodeDetail::evaluateNameTypeNode,
                &IHttpRouteNodeDetail::evaluateRegTypeNode,
                &IHttpRouteNodeDetail::evaluatePlainText,
                &IHttpRouteNodeDetail::evaluateUnMatchedNode
            };

            fragment = _fragment;
            type = IUrlFragmentNode::REGEXP_MATCH;
            for(const auto& fun : funs){
                if(std::mem_fn(fun)(this, fragment) == true){
                    break;
                }
            }
        }

        bool IHttpRouteNodeDetail::evaluatePlainText(const QString& nodeName)
        {
            static QRegularExpression plainTextType("^\\w+$");
            auto result = plainTextType.match(nodeName);
            if(result.hasMatch()){
                this->type = IUrlFragmentNode::TEXT_MATCH;
                return true;
            }
            return false;
        }

        bool IHttpRouteNodeDetail::evaluateTypeEmptyNode(const QString &nodeName)
        {
            static QRegularExpression regTypeEmpty("^<>$");
            auto result = regTypeEmpty.match(nodeName);
            if(result.hasMatch()){
                this->type = IUrlFragmentNode::FULL_MATCH;
                return true;
            }
            return false;
        }

        bool IHttpRouteNodeDetail::evaluateNameOnlyNode(const QString &nodeName)
        {
            static QRegularExpression regTypeNameOnly("^<(\\w+)>$");
            auto result = regTypeNameOnly.match(nodeName);
            if(result.hasMatch()){
                this->name = result.captured(1);
                this->type = IUrlFragmentNode::FULL_MATCH;
                return true;
            }
            return false;
        }

        bool IHttpRouteNodeDetail::evaluateNameTypeNode(const QString &nodeName)
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
                    this->type = IUrlFragmentNode::REGEXP_MATCH;
                    return true;
                }

                auto fun = IHttpManage::queryPathFunValidator(valueType);
                if(fun != nullptr){
                    this->funValidator = fun;
                    this->type = IUrlFragmentNode::FUNC_MATCH;
                    return true;
                }
            }else  {
                this->type = IUrlFragmentNode::FULL_MATCH;
                return true;
            }
            return false;
        }

        bool IHttpRouteNodeDetail::evaluateRegTypeNode(const QString &nodeName)
        {
            static QRegularExpression regTypeNameReg("^<(reg)?:(\\w*):(\\w*)>$");
            if(regTypeNameReg.match(nodeName).hasMatch()){
                auto result = regTypeNameReg.match(nodeName);
                this->type = IUrlFragmentNode::REGEXP_MATCH;
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

        bool IHttpRouteNodeDetail::evaluateUnMatchedNode(const QString &nodeName)
        {
            auto info = nodeName + " is not a valid expression, please check it";
            qFatal(info.toUtf8());
            return true;
        }
    };
}

IUrlFragmentNode IUrlFragmentNode::createNode(const QString &segment)
{
    return detail::IHttpRouteNodeDetail(segment);
}

$PackageWebCoreEnd



