#include "IHttpControllerNode.h"
#include "http/IHttpManage.h"
#include "core/util/ISpawnUtil.h"
#include "http/controller/detail/IHttpControllerAction.h"

$PackageWebCoreBegin

IHttpControllerNode::IHttpControllerNode(IHttpControllerNode* parent, const IHttpUrlFragment& fragment)
{
    this->parentNode = parent;
    routeNode = fragment;
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

IHttpControllerAction* IHttpControllerNode::setLeaf(const IHttpControllerAction &leafNode)
{
    auto ptr = getLeaf(leafNode.httpMethod);
    if(ptr){
        qFatal("Leaf already registered");
    }

    auto leaf = new IHttpControllerAction(leafNode);
    leaf->parentNode = this;
    switch (leafNode.httpMethod) {
    case IHttpMethod::GET:
        getMethodLeaf = leaf;
        break;
    case IHttpMethod::POST:
        postMethodLeaf = leaf;
        break;
    case IHttpMethod::PUT:
        putMethodLeaf = leaf;
        break;
    case IHttpMethod::DELETED:
        deleteMethodLeaf = leaf;
        break;
    case IHttpMethod::PATCH:
        patchMethodLeaf = leaf;
        break;
    case IHttpMethod::HEAD:
        getMethodLeaf = leaf;
        break;
    default:
        break;
    }
    return leaf;
}

IHttpControllerAction* IHttpControllerNode::getLeaf(IHttpMethod method)
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
    }
    return nullptr;
}

void IHttpControllerNode::addChildNode(const IHttpControllerNode& node)
{
    if(node.routeNode.type == IHttpUrlFragment::TEXT_MATCH){
        return this->children.prepend(node);
    }else if(node.routeNode.type == IHttpUrlFragment::FULL_MATCH){
        return this->children.append(node);
    }

    // process regMatch, this is placed between plain_Text and fullMatch
    // 需不需要 合并 fullMatch？, 答案是不需要，因为不仅仅是 需要正则式匹配，更是需要 名称绑定
    int index;
    for(index=0; index<children.length(); index++){
        if(children[index].routeNode.type != IHttpUrlFragment::TEXT_MATCH){
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
        if(val.routeNode.type == IHttpUrlFragment::TEXT_MATCH && val.routeNode.fragment == nodeName){
            nodes.append(&val);
        }else if(val.routeNode.type == IHttpUrlFragment::REGEXP_MATCH && val.routeNode.regexpValidator.match(nodeName).hasMatch()){
            nodes.append(&val);
        }else if(val.routeNode.type == IHttpUrlFragment::FUNC_MATCH && val.routeNode.funValidator(nodeName)){
            nodes.append(&val);
        }else if(val.routeNode.type == IHttpUrlFragment::FULL_MATCH){
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

// TODO: 看看是否能够省略这个东西
IHttpControllerNode *IHttpControllerNode::getOrAppendChildNode(const IHttpUrlFragment &fragment)
{
    if(!this->containFragment(fragment.fragment)){
        IHttpControllerNode childNode(this, fragment);
        this->addChildNode(childNode);
    }

    for(auto& child : children){
        if(child.routeNode.fragment == fragment.fragment){
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
                              << leaf->route.path
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
