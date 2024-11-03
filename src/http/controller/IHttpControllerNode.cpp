#include "IHttpControllerNode.h"
#include "http/IHttpManage.h"
#include "http/controller/detail/IHttpControllerAction.h"

$PackageWebCoreBegin

IHttpControllerNode::IHttpControllerNode(IHttpControllerNode* parent, const QString& fragment)
{
    this->parentNode = parent;
    routeNode = IUrlFragmentNode::createNode(fragment);
}

bool IHttpControllerNode::operator==(const IHttpControllerNode &node)
{
    return  routeNode.name == node.routeNode.name
            && routeNode.type == node.routeNode.type
            && routeNode.fragment == node.routeNode.fragment
            && children == node.children;
}

bool IHttpControllerNode::isEmpty() const
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
IHttpControllerAction* IHttpControllerNode::setLeaf(const IHttpControllerAction &leafNode)
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
IHttpControllerAction* IHttpControllerNode::getLeaf(IHttpMethod method)
{
    if(method == IHttpMethod::OPTIONS){
        return nullptr;
    }

    return getLeafRef(method);
}

void IHttpControllerNode::removeLeaf(IHttpMethod method)
{
    auto& ptr = getLeafRef(method);
    if(ptr != nullptr){
        delete ptr;
        ptr = nullptr;
    }
}

void IHttpControllerNode::addChildNode(const IHttpControllerNode& node)
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

void IHttpControllerNode::removeChildNode(const IHttpControllerNode &node)
{
    children.removeOne(node);
}

QVector<IHttpControllerNode *> IHttpControllerNode::getChildNodes(IStringView name)
{
    auto nodeName = name.toQString();   // TODO: fix latter;
    QVector<IHttpControllerNode*> nodes;
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

QVector<IHttpControllerNode *> IHttpControllerNode::getParentNodes()
{
    QVector<IHttpControllerNode*> parentNodes;
    IHttpControllerNode* val = this;
    while(val != nullptr){
        parentNodes.prepend(val);
        val = val->parentNode;
    }
    return parentNodes;
}

IHttpControllerNode *IHttpControllerNode::getOrAppendChildNode(const QString &fragment)
{
    if(!this->containFragment(fragment)){
        IHttpControllerNode childNode(this, fragment);
        this->addChildNode(childNode);
    }

    for(auto& child : children){
        if(child.routeNode.fragment == fragment){
            return &child;
        }
    }
    return nullptr;
}

IHttpControllerNode *IHttpControllerNode::getChildNode(const QString &fragment)
{
    for(auto& child : children){
        if(child.routeNode.fragment == fragment){
            return &child;
        }
    }
    return nullptr;
}

void IHttpControllerNode::travelPrint(int space) const
{
    if(isEmpty()){
        qDebug().noquote() << "  empty mapping";
        return;
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

IHttpControllerNode::IUrlActionNodePtr &IHttpControllerNode::getLeafRef(IHttpMethod method)
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

bool IHttpControllerNode::containFragment(const QString& fragment)
{
    for(const auto& child : children){
        if(child.routeNode.fragment == fragment){
            return true;
        }
    }
    return false;
}

$PackageWebCoreEnd
