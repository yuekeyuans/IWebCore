#include "IHttpControllerNode.h"
#include "http/IHttpManage.h"
#include "core/util/ISpawnUtil.h"
#include "http/controller/detail/IHttpControllerAction.h"

$PackageWebCoreBegin

IHttpControllerNode::IHttpControllerNode(IHttpControllerNode* parent, const IHttpUrlFragment& fragment)
{
//    this->parentNode = parent;
    urlFragment = fragment;
}

bool IHttpControllerNode::operator==(const IHttpControllerNode &node)
{
    return  urlFragment.name == node.urlFragment.name
            && urlFragment.type == node.urlFragment.type
            && urlFragment.fragment == node.urlFragment.fragment
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

void IHttpControllerNode::setLeaf(const IHttpControllerAction &leafNode)
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

void IHttpControllerNode::addChildNode(const IHttpUrlFragment &fragment)
{
    if(this->getChildNode(fragment)){
        return;
    }

    IHttpControllerNode childNode(this, fragment);
    this->addChildNode(childNode);
}

void IHttpControllerNode::addChildNode(const IHttpControllerNode& node)
{
    if(node.urlFragment.type == IHttpUrlFragment::TEXT_MATCH || ){
        return this->children.prepend(node);
    }else if(node.urlFragment.type == IHttpUrlFragment::FULL_MATCH){
        return this->children.append(node);
    }

    int index;
    for(index=0; index<children.length(); index++){
        if(children[index].urlFragment.type != IHttpUrlFragment::TEXT_MATCH){
            break;
        }
    }
    children.insert(index, node);
}

IHttpControllerNode *IHttpControllerNode::getChildNode(const IHttpUrlFragment &fragment)
{
    for(auto& child : children){
        if(child.urlFragment.fragment == fragment.fragment){
            return &child;
        }
    }
    return nullptr;
}

QVector<IHttpControllerNode *> IHttpControllerNode::getChildNodes(IStringView name)
{
    auto nodeName = name.toQString();   // TODO: fix latter;
    QVector<IHttpControllerNode*> nodes;
    for(auto& val : children){
        if(val.urlFragment.type == IHttpUrlFragment::TEXT_MATCH && val.urlFragment.fragment == nodeName){
            nodes.append(&val);
        }else if(val.urlFragment.type == IHttpUrlFragment::REGEXP_MATCH && val.urlFragment.regexpValidator.match(nodeName).hasMatch()){
            nodes.append(&val);
        }else if(val.urlFragment.type == IHttpUrlFragment::FUNC_MATCH && val.urlFragment.funValidator(nodeName)){
            nodes.append(&val);
        }else if(val.urlFragment.type == IHttpUrlFragment::FULL_MATCH){
            nodes.append(&val);
        }
    }
    return nodes;
}

void IHttpControllerNode::travelPrint(int space) const
{
    if(isEmpty()){
        qDebug().noquote() << "  empty mapping";
        return;
    }
    qDebug().noquote() << QString().fill(' ', 4* space) << "|" + this->urlFragment.fragment;

    auto print = [](IHttpControllerAction* leaf, int space){
        if(leaf != nullptr){
            qDebug().noquote()<< QString().fill(' ', 4 * space)
                              << "    |::" + IHttpMethodUtil::toString(leaf->httpMethod)
                              << leaf->route.path << "\t==>" << leaf->methodNode.signature;
        }
    };

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

$PackageWebCoreEnd
