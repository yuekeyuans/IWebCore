#include "IHttpControllerMapping.h"
#include "http/controller/IHttpControllerAction.h"
#include "http/controller/IHttpControllerNode.h"
#include "http/mappings/IHttpInternalErrorAction.h"
#include "http/net/IRequest.h"

$PackageWebCoreBegin

void IHttpControllerMapping::registerUrlActionNode(const IHttpControllerAction& node)
{
    auto ptr = &m_urlMapppings;
    for(const auto& fragment : node.m_path.m_fragments){
        if(!ptr->getChild(fragment)){
            ptr->addChild(fragment);
        }
        ptr = ptr->getChild(fragment);
    }
    ptr->setAction(node);
}

void IHttpControllerMapping::travelPrint() const
{
    qDebug().noquote() << QString::fromStdString(CLASS_NAME) << $order();
    m_urlMapppings.travelPrint();
    qDebug() << endl;
}

IHttpAction * IHttpControllerMapping::getAction(IRequest &request) const
{
    auto url = request.url();
    IHttpMethod method = request.method();

    auto nodePtr = &instance()->m_urlMapppings;
    if(url == "/"){
        return {nodePtr->getAction(method)};
    }

    IStringViewList fragments = url.split('/');
    if(fragments.first().empty()){
        fragments.pop_front();
    }

    auto actions = queryFunctionNodes(nodePtr, fragments, method);
    if(actions.empty()){
        return nullptr;
    }else if(actions.size() == 1){
        return actions.front();
    }
    return IHttpInternalErrorAction::instance();
}

std::vector<IHttpAction *> IHttpControllerMapping::queryFunctionNodes(const IHttpControllerNode *parentNode, const IStringViewList &fragments, IHttpMethod method) const
{
    std::vector<IHttpAction*> ret;
    auto childNodes = parentNode->getChildren(fragments.first());
    if(fragments.length() == 1){
        for(const auto& val : childNodes){
            auto action = val->getAction(method);
            if(action != nullptr){
                ret.push_back(action);
            }
        }
    }else{
        auto childFragments = fragments.mid(1);
        for(const auto& val : childNodes){
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

//bool IHttpControllerMapping::checkUrlDuplicateName(const IHttpControllerAction *node)
//{
//    QStringList names;
//    auto parent = static_cast<IHttpControllerNode*>(node->parentNode);

//    while(parent != nullptr){
//        auto name = parent->routeNode.name;
//        if(parent->routeNode.type != IHttpUrlFragment::TEXT_MATCH && !name.isEmpty()){
//            if(names.contains(name)){
//                auto info = name + " path variable name duplicated, please change one to annother name";
//                qFatal(info.toUtf8());
//                return false;
//            }
//            names.append(name);
//        }
//        parent = parent->parentNode;
//    }
//    return true;
//}

$PackageWebCoreEnd



