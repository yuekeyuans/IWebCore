#include "IControllerRouteMapping.h"
#include "IControllerManage.h"
#include "web/IWebAssert.h"
#include "web/node/IUrlActionNode.h"

$PackageWebCoreBegin

$UseAssert(IWebAssert)

IControllerRouteMapping::IControllerRouteMapping(IControllerRouteMapping* parent, const QString& fragment)
{
    this->parentNode = parent;
    evaluateNode(fragment);
}

bool IControllerRouteMapping::isEmpty() const
{
    if(!children.isEmpty()){
        return false;
    }

    auto funs = {
        getMethodLeaf,
        putMethodLeaf,
        postMethodLeaf,
        deleteMethodLeaf,
        patchMethodLeaf
    };
    for(auto fun : funs){
        if(fun != nullptr){
            return false;
        }
    }
    return true;
}

IUrlActionNode* IControllerRouteMapping::setLeaf(const IUrlActionNode &leafNode)
{
    auto& ptr = getLeafRef(leafNode.httpMethod);
    if(ptr != nullptr){
        delete ptr;
        ptr = nullptr;
        $Ast->warn("register_the_same_url");
    }

    auto leaf = new IUrlActionNode(leafNode);
    leaf->parentNode = this;
    ptr = leaf;

    return leaf;
}

// @see https://hc.apache.org/httpclient-legacy/methods/head.html
IUrlActionNode* IControllerRouteMapping::getLeaf(IHttpMethod method)
{
    if(method == IHttpMethod::OPTIONS){
        return nullptr;
    }

    return getLeafRef(method);
}

void IControllerRouteMapping::removeLeaf(IHttpMethod method)
{
    auto& ptr = getLeafRef(method);
    if(ptr != nullptr){
        delete ptr;
        ptr = nullptr;
    }
}

void IControllerRouteMapping::addChildNode(const IControllerRouteMapping& node)
{
    if(node.type == NodeType::TEXT_MATCH){
        return this->children.prepend(node);
    }else if(node.type == NodeType::FULL_MATCH){
        return this->children.append(node);
    }

    // process regMatch, this is placed between plain_Text and fullMatch
    // 需不需要 合并 fullMatch？, 答案是不需要，因为不仅仅是 需要正则式匹配，更是需要 名称绑定
    int index;
    for(index=0; index<children.length(); index++){
        if(children[index].type != NodeType::TEXT_MATCH){
            break;
        }
    }
    children.insert(index, node);
}

void IControllerRouteMapping::removeChildNode(const IControllerRouteMapping &node)
{
    children.removeOne(node);
}

QVector<IControllerRouteMapping *> IControllerRouteMapping::getChildNodes(const QString nodeName)
{
    QVector<IControllerRouteMapping*> nodes;
    for(auto& val : children){
        if(val.type == NodeType::TEXT_MATCH && val.fragment == nodeName){
            nodes.append(&val);
        }else if(val.type == NodeType::REGEXP_MATCH && val.regexpValidator.match(nodeName).hasMatch()){
            nodes.append(&val);
        }else if(val.type == NodeType::FUNC_MATCH && val.funValidator(nodeName)){
            nodes.append(&val);
        }else if(val.type == NodeType::FULL_MATCH){
            nodes.append(&val);
        }
    }
    return nodes;
}

QVector<IControllerRouteMapping *> IControllerRouteMapping::getParentNodes()
{
    QVector<IControllerRouteMapping*> parentNodes;
    IControllerRouteMapping* val = this;
    while(val != nullptr){
        parentNodes.prepend(val);
        val = val->parentNode;
    }
    return parentNodes;
}

IControllerRouteMapping *IControllerRouteMapping::getOrAppendChildNode(const QString &fragment)
{
    if(!this->containFragment(fragment)){
        IControllerRouteMapping childNode(this, fragment);
        this->addChildNode(childNode);
    }

    for(auto& child : children){
        if(child.fragment == fragment){
            return &child;
        }
    }
    return nullptr;
}

IControllerRouteMapping *IControllerRouteMapping::getChildNode(const QString &fragment)
{
    for(auto& child : children){
        if(child.fragment == fragment){
            return &child;
        }
    }
    return nullptr;
}

void IControllerRouteMapping::travelPrint(int space) const
{
    if(isEmpty()){
        return;
    }

    if(space == 0){
        qDebug() << "Below is Controller Url Mapping:";
    }

    auto print = [](IUrlActionNode* leaf, int space){
        if(leaf != nullptr){
            qDebug().noquote()<< QString().fill(' ', 4 * space)
                              << "    |::" + IHttpMethodHelper::toString(leaf->httpMethod)
                              << leaf->url
                              << "\t==>" << leaf->methodNode.expression;
        }
    };

    qDebug().noquote() << QString().fill(' ', 4* space)
                       << "|" + this->fragment;

    print(this->getMethodLeaf, space);
    print(this->putMethodLeaf, space);
    print(this->postMethodLeaf, space);
    print(this->deleteMethodLeaf, space);

    for(const auto& child: children){
        child.travelPrint(space + 1);
    }

    if(space == 0){
        qDebug() << "";
    }
}

bool IControllerRouteMapping::operator==(const IControllerRouteMapping &node)
{
    return this->name == node.name && type == node.type && fragment == node.fragment && children == node.children;
}

IControllerRouteMapping::IUrlActionNodePtr &IControllerRouteMapping::getLeafRef(IHttpMethod method)
{
    switch (method) {
    case IHttpMethod::GET:
        return getMethodLeaf;
    case IHttpMethod::POST:
        return postMethodLeaf;
    case IHttpMethod::PUT:
        return putMethodLeaf;
    case IHttpMethod::DELETED:
        return deleteMethodLeaf;
    case IHttpMethod::PATCH:
        return patchMethodLeaf;
    case IHttpMethod::HEAD:
        return getMethodLeaf;
    case IHttpMethod::OPTIONS:
        qFatal("options should not go here");
    default:
        qFatal("unknown method, this warning should not present");
    }
    return getMethodLeaf;
}

bool IControllerRouteMapping::containFragment(const QString& fragment)
{
    for(const auto& child : children){
        if(child.fragment == fragment){
            return true;
        }
    }
    return false;
}


void IControllerRouteMapping::evaluateNode(const QString &fragment)
{
    using FunType = bool (IControllerRouteMapping::*)(const QString&);
    static FunType funs[] = {
        &IControllerRouteMapping::evaluateTypeEmptyNode,
        &IControllerRouteMapping::evaluateNameOnlyNode,
        &IControllerRouteMapping::evaluateNameTypeNode,
        &IControllerRouteMapping::evaluateRegTypeNode,
        &IControllerRouteMapping::evaluatePlainText,
        &IControllerRouteMapping::evaluateUnMatchedNode
    };

    this->fragment = fragment;
    this->type = NodeType::REGEXP_MATCH;
    for(const auto& fun : funs){
        if(std::mem_fn(fun)(this, fragment) == true){
            break;
        }
    }
}

bool IControllerRouteMapping::evaluatePlainText(const QString& nodeName)
{
    static QRegularExpression plainTextType("^\\w+$");
    auto result = plainTextType.match(nodeName);
    if(result.hasMatch()){
        this->type = TEXT_MATCH;
        return true;
    }
    return false;
}

bool IControllerRouteMapping::evaluateTypeEmptyNode(const QString &nodeName)
{
    static QRegularExpression regTypeEmpty("^<>$");
    auto result = regTypeEmpty.match(nodeName);
    if(result.hasMatch()){
        this->type = FULL_MATCH;
        return true;
    }
    return false;
}

bool IControllerRouteMapping::evaluateNameOnlyNode(const QString &nodeName)
{
    static QRegularExpression regTypeNameOnly("^<(\\w+)>$");
    auto result = regTypeNameOnly.match(nodeName);
    if(result.hasMatch()){
        this->name = result.captured(1);
        this->type = FULL_MATCH;
        return true;
    }
    return false;
}

bool IControllerRouteMapping::evaluateNameTypeNode(const QString &nodeName)
{
    static QRegularExpression regTypeNameValue("^<(\\w*):(\\w*)>$");
    auto result = regTypeNameValue.match(nodeName);
    if(!result.hasMatch()){
        return false;
    }

    this->name = result.captured(1);
    auto valueType = result.captured(2);
    if(!valueType.isEmpty()){
        auto express = IControllerManage::queryPathRegValidator(valueType);
        if(!express.isEmpty()){
            this->regexpValidator = QRegularExpression(express);
            this->type = REGEXP_MATCH;
            return true;
        }

        auto fun = IControllerManage::queryPathFunValidator(valueType);
        if(fun != nullptr){
            this->funValidator = fun;
            this->type = FUNC_MATCH;
            return true;
        }
    }else  {
        this->type = FULL_MATCH;
        return true;
    }
    return false;
}

bool IControllerRouteMapping::evaluateRegTypeNode(const QString &nodeName)
{
    static QRegularExpression regTypeNameReg("^<(reg)?:(\\w*):(\\w*)>$");
    if(regTypeNameReg.match(nodeName).hasMatch()){
        auto result = regTypeNameReg.match(nodeName);
        this->type = REGEXP_MATCH;
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

bool IControllerRouteMapping::evaluateUnMatchedNode(const QString &nodeName)
{
    auto info = nodeName + " is not a valid expression, please check it";
    qFatal(info.toUtf8());
    return true;
}

$PackageWebCoreEnd
