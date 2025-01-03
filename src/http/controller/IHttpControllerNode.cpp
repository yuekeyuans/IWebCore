#include "IHttpControllerNode.h"
#include "http/IHttpManage.h"
#include "core/util/ISpawnUtil.h"
#include "http/controller/IHttpControllerAction.h"

$PackageWebCoreBegin

IHttpControllerNode::IHttpControllerNode(const IHttpPathFragment& fragment)
{
    urlFragment = fragment;
}

bool IHttpControllerNode::operator==(const IHttpControllerNode &node)
{
    return  urlFragment.m_name == node.urlFragment.m_name
            && urlFragment.m_type == node.urlFragment.m_type
            && urlFragment.m_fragment == node.urlFragment.m_fragment
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
    auto ptr = getAction(action.m_httpMethod);
    if(ptr){
        qFatal("action already registered");
    }

    auto newAction = new IHttpControllerAction(action);
    newAction->m_parentNode = this;
    switch (action.m_httpMethod) {
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

void IHttpControllerNode::addChild(const IHttpPathFragment &fragment)
{
    if(!this->getChild(fragment)){
        this->addChild(IHttpControllerNode{fragment});
    }
}

void IHttpControllerNode::addChild(const IHttpControllerNode& node)
{
    if(node.urlFragment.m_type == IHttpPathFragment::TEXT){
        return this->children.prepend(node);
    }else if(node.urlFragment.m_type == IHttpPathFragment::FULL_MATCH){
        return this->children.append(node);
    }

    int index;
    for(index=0; index<children.length(); index++){
        if(children[index].urlFragment.m_type != IHttpPathFragment::TEXT){
            break;
        }
    }
    children.insert(index, node);
}

IHttpControllerNode *IHttpControllerNode::getChild(const IHttpPathFragment &fragment)
{
    for(auto& child : children){
        if(child.urlFragment.m_fragment == fragment.m_fragment){
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
                              << "    |::" + IHttpMethodUtil::toString(action->m_httpMethod).toQString()
                              << "/" + action->m_path.m_path << "\t==>" << action->m_methodNode.signature;
        }
    };
    qDebug().noquote() << QString().fill(' ', 4* space) << "|" + this->urlFragment.m_fragment;
    print(this->getMethodAction, space);
    print(this->putMethodAction, space);
    print(this->postMethodAction, space);
    print(this->deleteMethodAction, space);
    for(const auto& child: children){
        child.travelPrint(space + 1);
    }
}

$PackageWebCoreEnd
