#include "IControllerManage.h"
#include "core/config/IContextManage.h"
#include "web/net/IRequest.h"
#include "core/base/IConvertUtil.h"
#include "core/base/IMetaUtil.h"
#include "web/net/impl/IReqRespRaw.h"
#include "web/IWebAssert.h"

$PackageWebCoreBegin

$UseAssert(IWebAssert)

namespace IControllerManageHelper {
    void registerCommonTypes();

    bool isShortValue(const QString& value);
    bool isUShortValue(const QString& value);
    bool isIntValue(const QString& value);
    bool isUIntValue(const QString& value);
    bool isLongValue(const QString& value);
    bool isULongValue(const QString& value);
    bool isLongLongValue(const QString& value);
    bool isULongLongValue(const QString& value);
    bool isFloatValue(const QString& value);
    bool isDoubleValue(const QString& value);

    bool isQDateValue(const QString& value);
    bool isQTimeValue(const QString& value);
    bool isQDateTimeValue(const QString& value);

    bool isQStringValue(const QString& value);
}

IControllerManage::IControllerManage()
{
    m_urlMapppings = std::make_shared<IControllerRouteNode>();
    m_fileMappings = std::make_shared<IControllerFileNode>();

    static std::once_flag flag;
    std::call_once(flag, [&](){
        IControllerManageHelper::registerCommonTypes(); // this won't be compile in Qt5 gcc
        preRegisterPathValidator();
    });
}

void IControllerManage::setIsServerStarted(bool value)
{
    auto inst = instance();
    inst->m_isServerStarted = value;
}

void IControllerManage::registerStatusActionNode(IStatusActionNode node)
{
    checkRegisterAvalible();

    auto inst = instance();
    if(inst->m_statusMappings.contains(node.httpStatus)){
        qDebug() << "override of status mapping";
    }
    inst->m_statusMappings[node.httpStatus] = node;
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

    auto inst = instance();
    if(inst->m_statusMappings.contains(node.httpStatus)){
        inst->m_statusMappings.remove(node.httpStatus);
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

    auto inst = instance();
    auto fragments = node.url.split("/");
    auto nodePtr = inst->m_urlMapppings.get();
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

    auto inst = instance();
    auto fragments = node.url.split("/");
    auto nodePtr = inst->m_urlMapppings.get();

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
        qFatal("dir not exist");
    }

    auto inst = instance();
    inst->m_fileMappings->mountMapping(dir.absolutePath(), prefix);
}

void IControllerManage::registerPathValidator(const QString &name, const QString &regexp)
{
    checkRegisterAvalible();

    auto inst = instance();
    QRegularExpression exp(regexp);
    if(!exp.isValid()){
        auto info = regexp + " : regular expression is not valid";
        qFatal(info.toUtf8());
    }

    if(inst->m_pathRegValidators.contains(name) || inst->m_pathFunValidators.contains(name)){
        auto info = name + " validator already registered";
        qFatal(info.toUtf8());
    }

    inst->m_pathRegValidators[name] = regexp;
}

void IControllerManage::registerPathValidator(const QString &name, ValidatorFun fun)
{
    checkRegisterAvalible();

    auto inst = instance();
    if(inst->m_pathFunValidators.contains(name) || inst->m_pathFunValidators.contains(name)){
        auto info = name + " validator already registered";
        qFatal(info.toUtf8());
    }

    inst->m_pathFunValidators[name] = fun;
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
    instance()->m_urlMapppings->travelPrint();
    instance()->m_fileMappings->travelPrint();
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

IUrlActionNode *IControllerManage::getUrlActionNode(IRequest &request)
{
    const QString &url = request.url();
    IHttpMethod method = request.method();

    auto nodePtr = instance()->m_urlMapppings.get();

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

QString IControllerManage::getStaticFileActionPath(const IRequest &request)
{
    auto inst = instance();
    return inst->m_fileMappings->getFilePath(request.url());
}

void IControllerManage::setDefaultStaticDir(const QString &dirPath)
{
    auto inst = instance();

    bool ok;
    auto value = IContextManage::instance()->getConfigAsString("PP_DEFAULT_STATIC_DIR", ok);
    if(!ok || value.isEmpty()){
        value = inst->m_staticFilePrefix;
    }

    if(!value.isEmpty()){
        IAssertInfo info;
        info.reason = QString("old: ").append(value).append(" new: ").append(dirPath);
        $Ast->fatal("static_file_dir_aleady_exist", info);
    }

    QDir dir(dirPath);
    if(!dir.exists()){
        IAssertInfo info;
        info.reason = QString("path: ").append(dirPath);
        $Ast->fatal("static_file_dir_not_exist", info);
    }

    inst->m_staticFilePrefix = dir.absolutePath().append("/");
}

// TODO: 先不动这个内容，这个应该是需要从 Profile 中间取出数据来初始化的，之后再看一看吧
QString IControllerManage::getDefaultStaticDir()
{
    auto inst = instance();
    bool ok;
    auto value = IContextManage::instance()->getConfigAsString("PP_DEFAULT_STATIC_DIR", ok);
    if(ok && !value.isEmpty()){
        inst->m_staticFilePrefix = value;       // 优先设置项。
    }

    if(inst->m_staticFilePrefix.isEmpty()){
        inst->m_staticFilePrefix = ":/";
    }

    return inst->m_staticFilePrefix;
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

QVector<IUrlActionNode *> IControllerManage::queryFunctionNodes(IControllerRouteNode *parentNode,
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

    IControllerRouteNode* routeNode = static_cast<IControllerRouteNode*>(node);
    QVector<IControllerRouteNode *>  nodes = routeNode->getParentNodes();
    nodes.pop_front();      // 去掉第一个node， 因为第一个 node 是 / 根节点，不参与。
    assert(nodes.length() == fragments.length());
    for(int i=0;i<nodes.length();i++){
        if(nodes[i]->type != IControllerRouteNode::TEXT_MATCH && !nodes[i]->name.isEmpty()){
            ret[nodes[i]->name] = fragments[i].toUtf8();
        }
    }
    return ret;
}

bool IControllerManage::checkUrlDuplicateName(const IUrlActionNode *node)
{
    QStringList names;
    auto parent = static_cast<IControllerRouteNode*>(node->parentNode);

    while(parent != nullptr){
        auto name = parent->name;
        if(parent->type != IControllerRouteNode::TEXT_MATCH && !name.isEmpty()){
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

void IControllerManage::preRegisterPathValidator()
{
    static QMap<QString, QString> validatorRegMap = {
        {"uuid",    "^[0-9a-f]{8}(-[0-9a-f]{4}){3}-[0-9a-f]{12}$"},
        {"base64",  "^[a-zA-Z0-9+/]*={0,2}$"},
    };

    static QMap<QString, ValidatorFun> validatorFunMap = {
        {"short", IControllerManageHelper::isShortValue},
        {"ushort", IControllerManageHelper::isUShortValue},
        {"int", IControllerManageHelper::isIntValue},
        {"uint", IControllerManageHelper::isUIntValue},
        {"long", IControllerManageHelper::isLongValue},
        {"ulong", IControllerManageHelper::isULongValue},
        {"longlong", IControllerManageHelper::isLongLongValue},
        {"ulonglong", IControllerManageHelper::isULongLongValue},
        {"float", IControllerManageHelper::isFloatValue},
        {"double", IControllerManageHelper::isDoubleValue},

        {"date", IControllerManageHelper::isQDateValue},
        {"QDate", IControllerManageHelper::isQDateValue},
        {"time", IControllerManageHelper::isQTimeValue},
        {"QTime", IControllerManageHelper::isQTimeValue},
        {"datetime", IControllerManageHelper::isQDateTimeValue},
        {"QDateTime", IControllerManageHelper::isQDateTimeValue},

        {"string", IControllerManageHelper::isQStringValue},
        {"QString", IControllerManageHelper::isQStringValue},
    };


    for(auto key : validatorRegMap.keys()){
        m_pathRegValidators[key] = validatorRegMap[key];
    }

    for(auto key : validatorFunMap.keys()){
        m_pathFunValidators[key] = validatorFunMap[key];
    }
}

void IControllerManage::checkRegisterAvalible()
{
    auto inst = instance();
    if(inst->m_isServerStarted){
        $Ast->fatal("register_to_controllerManage_error");
    }
}

void IControllerManageHelper::registerCommonTypes()
{
    IMetaUtil::registerMetaType<short>("short");
    IMetaUtil::registerMetaType<ushort>("ushort");
    IMetaUtil::registerMetaType<int>("int");
    IMetaUtil::registerMetaType<uint>("unit");
    IMetaUtil::registerMetaType<long>("long");
    IMetaUtil::registerMetaType<ulong>("ulong");
    IMetaUtil::registerMetaType<qlonglong>("qlonglong");
    IMetaUtil::registerMetaType<qulonglong>("qulonglong");
    IMetaUtil::registerMetaType<float>("float");
    IMetaUtil::registerMetaType<double>("double");

    IMetaUtil::registerMetaType<int16_t>("int16_t");
    IMetaUtil::registerMetaType<uint16_t>("uint16_t");
    IMetaUtil::registerMetaType<int32_t>("int32_t");
    IMetaUtil::registerMetaType<uint32_t>("uint32_t");
    IMetaUtil::registerMetaType<int64_t>("int64_t");
    IMetaUtil::registerMetaType<uint64_t>("uint64_t");

    IMetaUtil::registerMetaType<QString>("QString");
    IMetaUtil::registerMetaType<QByteArray>("QByteArray");
    IMetaUtil::registerMetaType<QJsonValue>("QJsonValue");
    IMetaUtil::registerMetaType<QJsonArray>("QJsonArray");
    IMetaUtil::registerMetaType<QJsonObject>("QJsonObject");
}

bool IControllerManageHelper::isShortValue(const QString& value){
    bool ok;
    value.toShort(&ok);
    return ok;
}
bool IControllerManageHelper::isUShortValue(const QString& value){
    bool ok;
    value.toUShort(&ok);
    return ok;
}
bool IControllerManageHelper::isIntValue(const QString& value){
    bool ok;
    value.toInt(&ok);
    return ok;
}
bool IControllerManageHelper::isUIntValue(const QString& value){
    bool ok;
    value.toUInt(&ok);
    return ok;
}
bool IControllerManageHelper::isLongValue(const QString& value){
    bool ok;
    value.toLong(&ok);
    return ok;
}
bool IControllerManageHelper::isULongValue(const QString& value){
    bool ok;
    value.toULong(&ok);
    return ok;
}
bool IControllerManageHelper::isLongLongValue(const QString& value){
    bool ok;
    value.toLongLong(&ok);
    return ok;
}
bool IControllerManageHelper::isULongLongValue(const QString& value){
    bool ok;
    value.toULongLong(&ok);
    return ok;
}
bool IControllerManageHelper::isFloatValue(const QString& value){
    bool ok;
    value.toFloat(&ok);
    return ok;
}
bool IControllerManageHelper::isDoubleValue(const QString& value){
    bool ok;
    value.toDouble(&ok);
    return ok;
}

bool IControllerManageHelper::isQDateValue(const QString& value){
    QVariant variant = value;
    return variant.toDate().isValid();
}
bool IControllerManageHelper::isQTimeValue(const QString& value){
    QVariant variant = value;
    return variant.toTime().isValid();
}
bool IControllerManageHelper::isQDateTimeValue(const QString& value){
    QVariant variant = value;
    return variant.toDateTime().isValid();
}

bool IControllerManageHelper::isQStringValue(const QString& value){
    return !value.isEmpty();
}

$PackageWebCoreEnd
