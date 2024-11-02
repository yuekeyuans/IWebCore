#include "IHttpRouteNode.h"
#include "http/controller/IHttpManage.h"
#include "http/controller/detail/IHttpControllerAction.h"

$PackageWebCoreBegin

IHttpRouteNode::IHttpRouteNode(IHttpRouteNode* parent, const QString& fragment)
{
    this->parentNode = parent;
    routeNode = IUrlFragmentNode::createNode(fragment);
}

bool IHttpRouteNode::operator==(const IHttpRouteNode &node)
{
    return  routeNode.name == node.routeNode.name
            && routeNode.type == node.routeNode.type
            && routeNode.fragment == node.routeNode.fragment
            && children == node.children;
}

bool IHttpRouteNode::isEmpty() const
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

// TODO: WARN
IHttpControllerAction* IHttpRouteNode::setLeaf(const IHttpControllerAction &leafNode)
{
    auto& ptr = getLeafRef(leafNode.httpMethod);
    if(ptr != nullptr){
        delete ptr;
        ptr = nullptr;
//        $Ast->warn("register_the_same_url");
    }

    auto leaf = new IHttpControllerAction(leafNode);
    leaf->parentNode = this;
    ptr = leaf;

    return leaf;
}

// @see https://hc.apache.org/httpclient-legacy/methods/head.html
IHttpControllerAction* IHttpRouteNode::getLeaf(IHttpMethod method)
{
    if(method == IHttpMethod::OPTIONS){
        return nullptr;
    }

    return getLeafRef(method);
}

void IHttpRouteNode::removeLeaf(IHttpMethod method)
{
    auto& ptr = getLeafRef(method);
    if(ptr != nullptr){
        delete ptr;
        ptr = nullptr;
    }
}

void IHttpRouteNode::addChildNode(const IHttpRouteNode& node)
{
    if(node.routeNode.type == IUrlFragmentNode::TEXT_MATCH){
        return this->children.prepend(node);
    }else if(node.routeNode.type == IUrlFragmentNode::FULL_MATCH){
        return this->children.append(node);
    }

    // process regMatch, this is placed between plain_Text and fullMatch
    // 需不需要 合并 fullMatch？, 答案是不需要，因为不仅仅是 需要正则式匹配，更是需要 名称绑定
    int index;
    for(index=0; index<children.length(); index++){
        if(children[index].routeNode.type != IUrlFragmentNode::TEXT_MATCH){
            break;
        }
    }
    children.insert(index, node);
}

void IHttpRouteNode::removeChildNode(const IHttpRouteNode &node)
{
    children.removeOne(node);
}

QVector<IHttpRouteNode *> IHttpRouteNode::getChildNodes(IStringView name)
{
    auto nodeName = name.toQString();   // TODO: fix latter;
    QVector<IHttpRouteNode*> nodes;
    for(auto& val : children){
        if(val.routeNode.type == IUrlFragmentNode::TEXT_MATCH && val.routeNode.fragment == nodeName){
            nodes.append(&val);
        }else if(val.routeNode.type == IUrlFragmentNode::REGEXP_MATCH && val.routeNode.regexpValidator.match(nodeName).hasMatch()){
            nodes.append(&val);
        }else if(val.routeNode.type == IUrlFragmentNode::FUNC_MATCH && val.routeNode.funValidator(nodeName)){
            nodes.append(&val);
        }else if(val.routeNode.type == IUrlFragmentNode::FULL_MATCH){
            nodes.append(&val);
        }
    }
    return nodes;
}

QVector<IHttpRouteNode *> IHttpRouteNode::getParentNodes()
{
    QVector<IHttpRouteNode*> parentNodes;
    IHttpRouteNode* val = this;
    while(val != nullptr){
        parentNodes.prepend(val);
        val = val->parentNode;
    }
    return parentNodes;
}

IHttpRouteNode *IHttpRouteNode::getOrAppendChildNode(const QString &fragment)
{
    if(!this->containFragment(fragment)){
        IHttpRouteNode childNode(this, fragment);
        this->addChildNode(childNode);
    }

    for(auto& child : children){
        if(child.routeNode.fragment == fragment){
            return &child;
        }
    }
    return nullptr;
}

IHttpRouteNode *IHttpRouteNode::getChildNode(const QString &fragment)
{
    for(auto& child : children){
        if(child.routeNode.fragment == fragment){
            return &child;
        }
    }
    return nullptr;
}

void IHttpRouteNode::travelPrint(int space) const
{
    if(isEmpty()){
        return;
    }

    if(space == 0){
        qDebug() << "Controller Url Mapping:";
    }

    auto print = [](IHttpControllerAction* leaf, int space){
        if(leaf != nullptr){
            qDebug().noquote()<< QString().fill(' ', 4 * space)
                              << "    |::" + IHttpMethodUtil::toString(leaf->httpMethod)
                              << leaf->url
                              << "\t==>" << leaf->methodNode.signature;
        }
    };

    qDebug().noquote() << QString().fill(' ', 4* space)
                       << "|" + this->routeNode.fragment;

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

IHttpRouteNode::IUrlActionNodePtr &IHttpRouteNode::getLeafRef(IHttpMethod method)
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

bool IHttpRouteNode::containFragment(const QString& fragment)
{
    for(const auto& child : children){
        if(child.routeNode.fragment == fragment){
            return true;
        }
    }
    return false;
}

$PackageWebCoreEnd
