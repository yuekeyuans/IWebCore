#include "IHttpManage.h"
#include "core/base/IConvertUtil.h"
#include "core/base/IMetaUtil.h"
#include "core/config/IContextManage.h"
#include "core/config/IProfileImport.h"
#include "http/net/IRequest.h"
#include "http/net/impl/IReqRespRaw.h"
#include "http/IHttpAssert.h"

$PackageWebCoreBegin

$UseAssert(IHttpAssert)

void IHttpManage::setIsServerStarted(bool value)
{
    auto inst = instance();
    inst->m_isServerStarted = value;
}


void IHttpManage::registerUrlActionNode(IUrlActionNode node)
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

void IHttpManage::registerUrlActionNodes(const QVector<IUrlActionNode> &functionNodes)
{
    for(auto& node : functionNodes){
        registerUrlActionNode(node);
    }
}

void IHttpManage::registerStaticFiles(const QString &path, const QString &prefix)
{
    checkRegisterAvalible();

    QDir dir(path);
    if(!dir.exists()){
        $Ast->fatal("static_file_dir_not_exist");
    }

    $Bool enabledFileStaticMapping("http.fileService.staticMapping");
    if(enabledFileStaticMapping){
        m_resourceMappings.mountMapping(dir.absolutePath(), prefix);
    }else{
        m_folderMappings.mountMapping(dir.absolutePath(), prefix);
    }
}

void IHttpManage::registerPathValidator(const QString &name, const QString &regexp)
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

void IHttpManage::registerPathValidator(const QString &name, ValidatorFun fun)
{
    checkRegisterAvalible();

    if(m_pathFunValidators.contains(name) || m_pathFunValidators.contains(name)){
        auto info = name + " validator already registered";
        qFatal(info.toUtf8());
    }

    m_pathFunValidators[name] = fun;
}

void IHttpManage::travalPrintUrlTree()
{
    instance()->m_urlMapppings.travelPrint();
    instance()->m_resourceMappings.travelPrint();
    instance()->m_folderMappings.travelPrint();
}

QString IHttpManage::queryPathRegValidator(const QString &path)
{
    auto inst = instance();
    if(inst->m_pathRegValidators.contains(path)){
        return inst->m_pathRegValidators[path];
    }
    return "";
}

IHttpManage::ValidatorFun IHttpManage::queryPathFunValidator(const QString &path)
{
    auto inst = instance();
    if(inst->m_pathFunValidators.contains(path)){
        return inst->m_pathFunValidators[path];
    }
    return nullptr;
}

bool IHttpManage::isUrlActionNodeEnabled() const
{
    return !m_urlMapppings.isEmpty();
}

IUrlActionNode *IHttpManage::getUrlActionNode(IRequest &request)
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
        auto info = url + " : " + IHttpMethodUtil::toString(method) + " matched multi-functions, please check";
        qFatal(info.toUtf8());
    }

    auto node = nodes.first();
    request.getRaw()->m_requestUrlParameters = getPathVariable(node->parentNode, fragments);
    return node;
}

bool IHttpManage::isStaticFileActionPathEnabled()
{
    return m_resourceMappings.isEnabled() || m_folderMappings.isEnabled();
}

QString IHttpManage::getStaticFileActionPath(const IRequest &request)
{
    static bool isResourceMapping = m_resourceMappings.isEnabled();
    if(isResourceMapping){
        QString value = m_resourceMappings.getFilePath(request.url());
        if(!value.isEmpty()){
            return value;
        }
    }

    static bool isDirMapping = m_folderMappings.isEnabled();
    if(isDirMapping){
        return m_folderMappings.getFilePath(request.url());
    }
    return {};
}

QStringList IHttpManage::getStaticFolderActionPath(const IRequest &request)
{
    auto url = request.url();
    if(!url.endsWith("/")){
        url.append("/");
    }
    static bool isResourceMapping = m_resourceMappings.isEnabled();
    if(isResourceMapping){
        return m_resourceMappings.getFileEntries(url);
    }

    static bool isDirMapping = m_folderMappings.isEnabled();
    if(isDirMapping){
        return m_folderMappings.getFileEntries(url);
    }

    return {};
}

QVector<IUrlActionNode *> IHttpManage::queryFunctionNodes(IHttpRouteMapping *parentNode,
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

QMap<QString, QByteArray> IHttpManage::getPathVariable(void* node, const QStringList &fragments)
{
    QMap<QString, QByteArray> ret;
    if(node == nullptr){
        return ret;
    }

    IHttpRouteMapping* routeNode = static_cast<IHttpRouteMapping*>(node);
    QVector<IHttpRouteMapping *>  nodes = routeNode->getParentNodes();
    nodes.pop_front();      // 去掉第一个node， 因为第一个 node 是 / 根节点，不参与。
    assert(nodes.length() == fragments.length());
    for(int i=0;i<nodes.length();i++){
        if(nodes[i]->type != IHttpRouteMapping::TEXT_MATCH && !nodes[i]->name.isEmpty()){
            ret[nodes[i]->name] = fragments[i].toUtf8();
        }
    }
    return ret;
}

bool IHttpManage::checkUrlDuplicateName(const IUrlActionNode *node)
{
    QStringList names;
    auto parent = static_cast<IHttpRouteMapping*>(node->parentNode);

    while(parent != nullptr){
        auto name = parent->name;
        if(parent->type != IHttpRouteMapping::TEXT_MATCH && !name.isEmpty()){
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

void IHttpManage::checkRegisterAvalible()
{
    auto inst = instance();
    if(inst->m_isServerStarted){
        $Ast->fatal("register_to_controllerManage_error");
    }
}


$PackageWebCoreEnd
