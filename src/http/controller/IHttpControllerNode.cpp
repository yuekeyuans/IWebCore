#include "IHttpControllerNode.h"
#include "http/IHttpManage.h"
#include "core/util/ISpawnUtil.h"
#include "http/controller/IHttpControllerAction.h"

$PackageWebCoreBegin

IHttpControllerNode::IHttpControllerNode(const IHttpUrlFragment& fragment)
{
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
        getMethodAction,
        putMethodAction,
        postMethodAction,
        deleteMethodAction,
        patchMethodAction
    };
    for(auto fun : funs){
        if(fun != nullptr){
            return false;
        }
    }
    return true;
}

void IHttpControllerNode::setAction(const IHttpControllerAction &action)
{
    auto ptr = getAction(action.httpMethod);
    if(ptr){
        qFatal("action already registered");
    }

    auto newAction = new IHttpControllerAction(action);
    newAction->parentNode = this;
    switch (action.httpMethod) {
    case IHttpMethod::GET:
        getMethodAction = newAction;
        break;
    case IHttpMethod::POST:
        postMethodAction = newAction;
        break;
    case IHttpMethod::PUT:
        putMethodAction = newAction;
        break;
    case IHttpMethod::DELETED:
        deleteMethodAction = newAction;
        break;
    case IHttpMethod::PATCH:
        patchMethodAction = newAction;
        break;
    case IHttpMethod::HEAD:
        getMethodAction = newAction;
        break;
    default:
        break;
    }
}

IHttpControllerAction* IHttpControllerNode::getAction(IHttpMethod method) const
{
    switch (method) {
    case IHttpMethod::GET:
        return getMethodAction;
    case IHttpMethod::POST:
        return postMethodAction;
    case IHttpMethod::PUT:
        return putMethodAction;
    case IHttpMethod::DELETED:
        return deleteMethodAction;
    case IHttpMethod::PATCH:
        return patchMethodAction;
    case IHttpMethod::HEAD:
        return getMethodAction;
    }
    return nullptr;
}

void IHttpControllerNode::addChild(const IHttpUrlFragment &fragment)
{
    if(!this->getChild(fragment)){
        this->addChild(IHttpControllerNode{fragment});
    }
}

void IHttpControllerNode::addChild(const IHttpControllerNode& node)
{
    if(node.urlFragment.type == IHttpUrlFragment::TEXT_MATCH){
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

IHttpControllerNode *IHttpControllerNode::getChild(const IHttpUrlFragment &fragment)
{
    for(auto& child : children){
        if(child.urlFragment.fragment == fragment.fragment){
            return &child;
        }
    }
    return nullptr;
}

QVector<const IHttpControllerNode *> IHttpControllerNode::getChildren(IStringView name) const
{
    QVector<const IHttpControllerNode*> nodes;
    for(auto& val : children){
        if(val.urlFragment.isMatch(name)){
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
    auto print = [](IHttpControllerAction* action, int space){
        if(action){
            qDebug().noquote()<< QString().fill(' ', 4 * space)
                              << "    |::" + IHttpMethodUtil::toString(action->httpMethod)
                              << action->route.path << "\t==>" << action->methodNode.signature;
        }
    };
    qDebug().noquote() << QString().fill(' ', 4* space) << "|" + this->urlFragment.fragment;
    print(this->getMethodAction, space);
    print(this->putMethodAction, space);
    print(this->postMethodAction, space);
    print(this->deleteMethodAction, space);
    for(const auto& child: children){
        child.travelPrint(space + 1);
    }
}

$PackageWebCoreEnd
