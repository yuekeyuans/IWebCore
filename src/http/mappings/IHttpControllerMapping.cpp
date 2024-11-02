#include "IHttpControllerMapping.h"
#include "http/controller/detail/IHttpControllerAction.h"
#include "http/controller/detail/IHttpRouteNode.h"
#include "http/net/IRequest.h"
#include "http/net/impl/IRequestRaw.h"

$PackageWebCoreBegin

void IHttpControllerMapping::registerUrlActionNode(IHttpControllerAction node)
{
    checkRegisterAvalible();

    auto fragments = node.url.split("/");
    auto nodePtr = &m_urlMapppings;
    for(auto it=fragments.begin(); it!= fragments.end(); ++it){
        if(!it->isEmpty()){     // this step to guarantee the root element to settle properly
            nodePtr = nodePtr->getOrAppendChildNode(*it);
        }
    }
    auto newLeaf = nodePtr->setLeaf(node);
    checkUrlDuplicateName(newLeaf);  // TODO: delete from here
}

void IHttpControllerMapping::registerUrlActionNodes(const QVector<IHttpControllerAction> &functionNodes)
{
    for(auto& node : functionNodes){
        registerUrlActionNode(node);
    }
}

void IHttpControllerMapping::travelPrint()
{
    m_urlMapppings.travelPrint();
}


// TODO: 这个需要检查一下
std::vector<IHttpAction *> IHttpControllerMapping::getActions(IRequest &request)
{
    IStringView url = request.url();
    IHttpMethod method = request.method();

    auto nodePtr = &instance()->m_urlMapppings;

    if(url == "/"){
        return {nodePtr->getLeaf(method)};
    }

    IStringViewList fragments = url.split('/');
    if(fragments.first().empty()){
        fragments.pop_front();
    }

    return queryFunctionNodes(nodePtr, fragments, method);

// TODO: 这里对于 PathVariable 需要重新处理
//    std::vector<IHttpControllerAction*> nodes =  queryFunctionNodes(nodePtr, fragments, method);
//    if(nodes.length() == 0){
//        return {};
//    }else if(nodes.length() > 1){
//        auto info = url.toQString() + " : " + IHttpMethodUtil::toString(method) + " matched multi-functions, please check";
//        qFatal(info.toUtf8());
//    }

//    auto node = nodes.first();
//    request.getRaw()->m_requestUrlParameters = getPathVariable(node->parentNode, fragments);
//    return {node};
}

bool IHttpControllerMapping::checkUrlDuplicateName(const IHttpControllerAction *node)
{
    QStringList names;
    auto parent = static_cast<IHttpRouteNode*>(node->parentNode);

    while(parent != nullptr){
        auto name = parent->routeNode.name;
        if(parent->routeNode.type != IUrlFragmentNode::TEXT_MATCH && !name.isEmpty()){
            if(names.contains(name)){
                auto info = name + " path variable name duplicated, please change one to annother name";
                qFatal(info.toUtf8());
                return false;
            }
            names.append(name);
        }
        parent = parent->parentNode;
    }
    return true;
}

void IHttpControllerMapping::checkRegisterAvalible()
{
    // do nothing
}

std::vector<IHttpAction *> IHttpControllerMapping::queryFunctionNodes(IHttpRouteNode *parentNode, const IStringViewList &fragments, IHttpMethod method)
{
    // FIXME:

    std::vector<IHttpAction*> ret;
    auto childNodes = parentNode->getChildNodes(fragments.first());
    if(fragments.length() == 1){
        for(const auto& val : childNodes){
            auto leaf = val->getLeaf(method);
            if(leaf != nullptr){
                ret.push_back(leaf);
            }
        }
    }else{
        auto childFragments = fragments.mid(1);
        for(auto& val : childNodes){
            auto result = queryFunctionNodes(val, childFragments, method);
            if(!result.empty()){
                for(auto action : result){
                    ret.push_back(action);
                }
            }
        }
    }
    return ret;
}

QMap<IStringView, IStringView> IHttpControllerMapping::getPathVariable(void *node, const IStringViewList &fragments)
{
    // FIXME:
    return {};

    //    QMap<QString, QString> ret;
//    if(node == nullptr){
//        return ret;
//    }

//    IHttpRouteMapping* routeNode = static_cast<IHttpRouteMapping*>(node);
//    QVector<IHttpRouteMapping *>  nodes = routeNode->getParentNodes();
//    nodes.pop_front();      // 去掉第一个node， 因为第一个 node 是 / 根节点，不参与。
//    assert(nodes.length() == fragments.length());
//    for(int i=0;i<nodes.length();i++){
//        if(nodes[i]->type != IHttpRouteMapping::TEXT_MATCH && !nodes[i]->name.isEmpty()){
//            ret[nodes[i]->name] = fragments[i];
//        }
//    }
//    return ret;
}

$PackageWebCoreEnd



