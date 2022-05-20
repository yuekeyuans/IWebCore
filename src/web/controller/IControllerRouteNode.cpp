#include "IControllerRouteNode.h"
#include "IControllerManage.h"
#include "web/node/IUrlFunctionNode.h"

$PackageWebCoreBegin

IControllerRouteNode::IControllerRouteNode(IControllerRouteNode*parent, const QString& nodeName)
{
    this->parentNode = parent;
    evaluateNode(nodeName);
}

IUrlFunctionNode* IControllerRouteNode::setLeaf(const IUrlFunctionNode &leafNode)
{
    QMap<IHttpMethod, IUrlFunctionNode**> map = {
        {IHttpMethod::GET,      &this->getMethodLeaf },
        {IHttpMethod::POST,     &this->postMethodLeaf },
        {IHttpMethod::PUT,      &this->putMethodLeaf },
        {IHttpMethod::DELETED,  &this->deleteMethodLeaf },
        {IHttpMethod::PATCH,    &this->patchMethodLeaf }
    };

    auto leaf = new IUrlFunctionNode(leafNode);
    leaf->parentNode = this;
    for(auto key : map.keys()){
        if(leaf->httpMethod == key && *map[key] == nullptr){
            *map[key] = leaf;
            return leaf;
        }
    }
    qFatal("registration can`t match the leaf or the leaf already exist");
    return nullptr;
}

// @see https://hc.apache.org/httpclient-legacy/methods/head.html
IUrlFunctionNode* IControllerRouteNode::getLeaf(IHttpMethod method)
{
    switch (method) {
    case IHttpMethod::GET:
        return this->getMethodLeaf;
    case IHttpMethod::PUT:
        return this->putMethodLeaf;
    case IHttpMethod::POST:
        return this->postMethodLeaf;
    case IHttpMethod::DELETED:
        return this->deleteMethodLeaf;
    case IHttpMethod::PATCH:
        return this->patchMethodLeaf;
    case IHttpMethod::HEAD:
        return this->getMethodLeaf;                     // @see IResponse::respond
    case IHttpMethod::OPTIONS:
        break;                                          // @see IHttpSocketBase::handleOptionsRequest
    default:
        return nullptr;
    }
    return nullptr;
}

void IControllerRouteNode::addChildNode(const IControllerRouteNode& node)
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

QVector<IControllerRouteNode *> IControllerRouteNode::getChildNodes(const QString nodeName)
{
    QVector<IControllerRouteNode*> nodes;
    for(auto& val : children){
        if(val.type == NodeType::TEXT_MATCH && val.fragment == nodeName){
            nodes.append(&val);
            continue;
        }else if(val.type == NodeType::REGEXP_MATCH && val.regexpValidator.match(nodeName).hasMatch()){
            nodes.append(&val);
            continue;
        }else if(val.type == NodeType::FUNC_MATCH && val.funValidator(nodeName)){
            nodes.append(&val);
            continue;
        }else if(val.type == NodeType::FULL_MATCH){
            nodes.append(&val);
            continue;
        }
    }
    return nodes;
}

QVector<IControllerRouteNode *> IControllerRouteNode::getParentNodes()
{
    QVector<IControllerRouteNode*> parentNodes;
    IControllerRouteNode* val = this;
    while(val != nullptr){
        parentNodes.prepend(val);
        val = val->parentNode;
    }
    return parentNodes;
}

IControllerRouteNode *IControllerRouteNode::getOrAppendChildNode(const QString &nodeName)
{
    if(!this->contains(nodeName)){
        IControllerRouteNode childNode(this, nodeName);
        this->addChildNode(childNode);
    }

    for(auto& child : children){
        if(child.fragment == nodeName){
            return &child;
        }
    }
    return nullptr;
}

void IControllerRouteNode::travelPrint(int space) const
{
    if(space == 0){
        qDebug() << "============== url mapping begin =============";
    }

    auto print = [](IUrlFunctionNode* leaf, int space){
        if(leaf == nullptr) return;
        qDebug().noquote()<< QString().fill(' ', 4* space + 2)
                          << leaf->url
                          << IHttpMethodHelper::toString(leaf->httpMethod)
                          << "<==" << leaf->functionNode.funExpression;
    };

    qDebug().noquote() << QString().fill(' ', 4* space) << (this->fragment.isEmpty() ? "/" :this->fragment);

    print(this->getMethodLeaf, space);
    print(this->putMethodLeaf, space);
    print(this->postMethodLeaf, space);
    print(this->deleteMethodLeaf, space);

    for(const auto& child: children){
        child.travelPrint(space + 1);
    }

    if(space == 0){
        qDebug() << "=============== url mapping end ==============";
    }
}

bool IControllerRouteNode::contains(const QString& nodeName)
{
    for(const auto& child : children){
        if(child.fragment == nodeName){
            return true;
        }
    }
    return false;
}


void IControllerRouteNode::evaluateNode(const QString &nodeName)
{
    using FunType = bool (IControllerRouteNode::*)(const QString&);
    static FunType funs[] = {
        &IControllerRouteNode::evaluateTypeEmptyNode,
        &IControllerRouteNode::evaluateNameOnlyNode,
        &IControllerRouteNode::evaluateNameTypeNode,
        &IControllerRouteNode::evaluateRegTypeNode,
        &IControllerRouteNode::evaluatePlainText,
        &IControllerRouteNode::evaluateUnMatchedNode
    };

    this->fragment = nodeName;
    this->type = NodeType::REGEXP_MATCH;
    for(const auto& fun : funs){
        if(std::mem_fn(fun)(this, nodeName) == true){
            break;
        }
    }
}

bool IControllerRouteNode::evaluatePlainText(const QString& nodeName)
{
    static QRegularExpression plainTextType("^\\w+$");
    auto result = plainTextType.match(nodeName);
    if(result.hasMatch()){
        this->type = TEXT_MATCH;
        return true;
    }
    return false;
}

bool IControllerRouteNode::evaluateTypeEmptyNode(const QString &nodeName)
{
    static QRegularExpression regTypeEmpty("^<>$");
    auto result = regTypeEmpty.match(nodeName);
    if(result.hasMatch()){
        this->type = FULL_MATCH;
        return true;
    }
    return false;
}

bool IControllerRouteNode::evaluateNameOnlyNode(const QString &nodeName)
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

bool IControllerRouteNode::evaluateNameTypeNode(const QString &nodeName)
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

bool IControllerRouteNode::evaluateRegTypeNode(const QString &nodeName)
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

bool IControllerRouteNode::evaluateUnMatchedNode(const QString &nodeName)
{
    auto info = nodeName + " is not a valid expression, please check it";
    qFatal(info.toUtf8());
    return true;
}

$PackageWebCoreEnd
