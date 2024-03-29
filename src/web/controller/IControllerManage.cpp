#include "IControllerManage.h"
#include "core/base/IConvertUtil.h"
#include "core/base/IMetaUtil.h"
#include "core/config/IContextManage.h"
#include "core/config/IProfileImport.h"
#include "web/net/IRequest.h"
#include "web/net/impl/IReqRespRaw.h"
#include "web/IWebAssert.h"

$PackageWebCoreBegin

$UseAssert(IWebAssert)

void IControllerManage::setIsServerStarted(bool value)
{
    auto inst = instance();
    inst->m_isServerStarted = value;
}

void IControllerManage::registerStatusActionNode(IStatusActionNode node)
{
    checkRegisterAvalible();

    if(m_statusMappings.contains(node.httpStatus)){
        qDebug() << "override of status mapping";
    }
    m_statusMappings[node.httpStatus] = node;
}

void IControllerManage::registerStatusActionNodes(const QVector<IStatusActionNode> &statusNodes)
{
    for(const auto& node : statusNodes){
        registerStatusActionNode(node);
    }
}

void IControllerManage::unRegisterStatusActionNode(const IStatusActionNode &node)
{
    checkRegisterAvalible();

    if(m_statusMappings.contains(node.httpStatus)){
        m_statusMappings.remove(node.httpStatus);
    }
}

void IControllerManage::unRegisterStatusActionNodes(const QVector<IStatusActionNode> &statusNodes)
{
    for(const auto& node : statusNodes){
        unRegisterStatusActionNode(node);
    }
}

void IControllerManage::registerUrlActionNode(IUrlActionNode node)
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
    checkUrlDuplicateName(newLeaf);
}

void IControllerManage::registerUrlActionNodes(const QVector<IUrlActionNode> &functionNodes)
{
    for(auto& node : functionNodes){
        registerUrlActionNode(node);
    }
}

void IControllerManage::unRegisterUrlActionNode(IUrlActionNode node)
{
    checkRegisterAvalible();

    auto fragments = node.url.split("/");
    auto nodePtr = &m_urlMapppings;

    for(const auto& fragment : fragments){
        nodePtr = nodePtr->getChildNode(fragment);
        if(nodePtr == nullptr){
            return;                  // 结束处理，因为没有相对应的内容
        }
    }

    nodePtr->removeLeaf(node.httpMethod);
    while(nodePtr != nullptr && nodePtr->parentNode != nullptr && nodePtr->isEmpty()){
        auto parent = nodePtr->parentNode;
        parent->removeChildNode(*nodePtr);
        nodePtr = parent;
    }
}

void IControllerManage::unRegisterUrlActionNodes(const QVector<IUrlActionNode> &functionNodes)
{
    for(auto& node : functionNodes){
        unRegisterUrlActionNode(node);
    }
}

void IControllerManage::registerStaticFiles(const QString &path, const QString &prefix)
{
    checkRegisterAvalible();

    QDir dir(path);
    if(!dir.exists()){
        $Ast->fatal("static_file_dir_not_exist");
    }

    $Bool enabledFileStaticMapping("http.fileService.staticMapping", false);

    if(enabledFileStaticMapping.isLoaded() && enabledFileStaticMapping){
        m_resourceMappings.mountMapping(dir.absolutePath(), prefix);
    }else{
        m_directoryMappings.mountMapping(dir.absolutePath(), prefix);
    }
}

void IControllerManage::registerPathValidator(const QString &name, const QString &regexp)
{
    checkRegisterAvalible();

    QRegularExpression exp(regexp);
    if(!exp.isValid()){
        auto info = regexp + " : regular expression is not valid";
        qFatal(info.toUtf8());
    }

    if(m_pathRegValidators.contains(name) || m_pathFunValidators.contains(name)){
        auto info = name + " validator already registered";
        qFatal(info.toUtf8());
    }

    m_pathRegValidators[name] = regexp;
}

void IControllerManage::registerPathValidator(const QString &name, ValidatorFun fun)
{
    checkRegisterAvalible();

    if(m_pathFunValidators.contains(name) || m_pathFunValidators.contains(name)){
        auto info = name + " validator already registered";
        qFatal(info.toUtf8());
    }

    m_pathFunValidators[name] = fun;
}

void IControllerManage::registerPreProcessor(IProcessorWare *middleWare)
{
    checkRegisterAvalible();

    auto inst = instance();
    inst->m_preProcessors.append(middleWare);
}

void IControllerManage::registerPostProcessor(IProcessorWare *middleWare)
{
    checkRegisterAvalible();

    auto inst = instance();
    inst->m_postProcessors.append(middleWare);
}

void IControllerManage::registerPreInterceptor(IInterceptorWare *middleWare)
{
    checkRegisterAvalible();

    auto inst = instance();
    inst->m_preInterceptors.append(middleWare);
}

void IControllerManage::registerPostInterceptor(IInterceptorWare *middleWare)
{
    checkRegisterAvalible();

    auto inst = instance();
    inst->m_postInterceptors.append(middleWare);
}

void IControllerManage::travalPrintUrlTree()
{
    instance()->m_urlMapppings.travelPrint();
    instance()->m_resourceMappings.travelPrint();
    instance()->m_directoryMappings.travelPrint();
}

QString IControllerManage::queryPathRegValidator(const QString &path)
{
    auto inst = instance();
    if(inst->m_pathRegValidators.contains(path)){
        return inst->m_pathRegValidators[path];
    }
    return "";
}

IControllerManage::ValidatorFun IControllerManage::queryPathFunValidator(const QString &path)
{
    auto inst = instance();
    if(inst->m_pathFunValidators.contains(path)){
        return inst->m_pathFunValidators[path];
    }
    return nullptr;
}

bool IControllerManage::isUrlActionNodeEnabled() const
{
    return !m_urlMapppings.isEmpty();
}

IUrlActionNode *IControllerManage::getUrlActionNode(IRequest &request)
{
    const QString &url = request.url();
    IHttpMethod method = request.method();

    auto nodePtr = &instance()->m_urlMapppings;

    if(url == "/"){
        return nodePtr->getLeaf(method);
    }

    auto fragments = url.split("/");
    if(fragments.first().isEmpty()){
        fragments.pop_front();
    }

    QVector<IUrlActionNode*> nodes =  queryFunctionNodes(nodePtr, fragments, method);
    if(nodes.length() == 0){
        return nullptr;
    }else if(nodes.length() > 1){
        auto info = url + " : " + IHttpMethodHelper::toString(method) + " matched multi-functions, please check";
        qFatal(info.toUtf8());
    }

    auto node = nodes.first();
    request.getRaw()->m_requestUrlParameters = getPathVariable(node->parentNode, fragments);
    return node;
}

IStatusActionNode *IControllerManage::getStatusActionNode(IHttpStatus status)
{
    auto inst = instance();
    if(inst->m_statusMappings.contains(status)){
        return &inst->m_statusMappings[status];
    }
    return nullptr;
}

bool IControllerManage::isStaticFileActionPathEnabled()
{
    return m_resourceMappings.isEnabled() || m_directoryMappings.isEnabled();
}

QString IControllerManage::getStaticFileActionPath(const IRequest &request)
{
    static bool isResourceMapping = m_resourceMappings.isEnabled();
    if(isResourceMapping){
        QString value = m_resourceMappings.getFilePath(request.url());
        if(!value.isEmpty()){
            return value;
        }
    }

    static bool isDirMapping = m_directoryMappings.isEnabled();
    if(isDirMapping){
        return m_directoryMappings.getFilePath(request.url());
    }
    return {};
}

QStringList IControllerManage::getStaticDirectoryActionPath(const IRequest &request)
{
    auto url = request.url();
    static bool isResourceMapping = m_resourceMappings.isEnabled();
    if(isResourceMapping){
        return m_resourceMappings.getFileEntries(url);
    }

    static bool isDirMapping = m_directoryMappings.isEnabled();
    if(isDirMapping){
        return m_directoryMappings.getFileEntries(url);
    }
    return {};
}

bool IControllerManage::preIntercept(IRequest &request, IResponse &response)
{
    auto inst = instance();
    for(auto obj : inst->m_preInterceptors){
        if(obj->match(request, response)
            && obj->action(request, response)){
            return true;
        }
    }
    return false;
}

bool IControllerManage::postIntercept(IRequest &request, IResponse &response)
{
    auto inst = instance();
    for(auto obj : inst->m_postInterceptors){
        if(obj->match(request, response)
            && obj->action(request, response)){
            return true;
        }
    }
    return false;
}

bool IControllerManage::preProcess(IRequest &request, IResponse &response)
{
    auto inst = instance();
    for(auto obj : inst->m_preProcessors){
        if(obj->match(request, response)){
            obj->action(request, response);
        }
    }
    return true;
}

bool IControllerManage::postProcess(IRequest &request, IResponse &response)
{
    auto inst = instance();
    for(auto obj : inst->m_postProcessors){
        if(obj->match(request, response)){
            obj->action(request, response);
        }
    }
    return true;
}

QVector<IUrlActionNode *> IControllerManage::queryFunctionNodes(IControllerRouteMapping *parentNode,
                                                             const QStringList &fragments, IHttpMethod method)
{
    QVector<IUrlActionNode*> ret;
    auto childNodes = parentNode->getChildNodes(fragments.first());
    if(fragments.length() == 1){
        for(const auto& val : childNodes){
            auto leaf = val->getLeaf(method);
            if(leaf != nullptr){
                ret.append(leaf);
            }
        }
    }else{
        auto childFragments = fragments.mid(1);
        for(auto& val : childNodes){
            auto result = queryFunctionNodes(val, childFragments, method);
            if(!result.isEmpty()){
                ret.append(result);
            }
        }
    }
    return ret;
}

QMap<QString, QByteArray> IControllerManage::getPathVariable(void* node, const QStringList &fragments)
{
    QMap<QString, QByteArray> ret;
    if(node == nullptr){
        return ret;
    }

    IControllerRouteMapping* routeNode = static_cast<IControllerRouteMapping*>(node);
    QVector<IControllerRouteMapping *>  nodes = routeNode->getParentNodes();
    nodes.pop_front();      // 去掉第一个node， 因为第一个 node 是 / 根节点，不参与。
    assert(nodes.length() == fragments.length());
    for(int i=0;i<nodes.length();i++){
        if(nodes[i]->type != IControllerRouteMapping::TEXT_MATCH && !nodes[i]->name.isEmpty()){
            ret[nodes[i]->name] = fragments[i].toUtf8();
        }
    }
    return ret;
}

bool IControllerManage::checkUrlDuplicateName(const IUrlActionNode *node)
{
    QStringList names;
    auto parent = static_cast<IControllerRouteMapping*>(node->parentNode);

    while(parent != nullptr){
        auto name = parent->name;
        if(parent->type != IControllerRouteMapping::TEXT_MATCH && !name.isEmpty()){
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

void IControllerManage::checkRegisterAvalible()
{
    auto inst = instance();
    if(inst->m_isServerStarted){
        $Ast->fatal("register_to_controllerManage_error");
    }
}


$PackageWebCoreEnd
