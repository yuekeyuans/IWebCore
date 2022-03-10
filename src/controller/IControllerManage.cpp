#include "IControllerManage.h"
#include "common/net/IRequest.h"
#include "base/IConvertUtil.h"
#include "base/IMetaUtil.h"
#include "common/net/impl/IReqRespRaw.h"

$PackageWebCoreBegin

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

IControllerManage::IControllerManage() : m_urlMapppings(new IControllerRouteNode)
{
    static std::once_flag flag;
    std::call_once(flag, [&](){
        IControllerManageHelper::registerCommonTypes(); // this won't be compile in Qt5 gcc
        preRegisterPathValidator();
    });
}

void IControllerManage::registerStatusFunctions(const QVector<IStatusFunctionNode> &statusNodes)
{
    auto inst = instance();
    for(const auto& node : statusNodes){
        if(inst->m_statusMappings.contains(node.httpStatus)){
            qDebug() << "override of status mapping";
        }
        inst->m_statusMappings[node.httpStatus] = node;
    }
}

void IControllerManage::registerUrlFunctions(const QVector<IUrlFunctionNode> &functionLeaves)
{
    auto inst = instance();
    for(auto& leaf : functionLeaves){
        auto fragments = leaf.url.split("/");
        auto nodePtr = inst->m_urlMapppings.get();
        for(auto it=fragments.begin(); it!= fragments.end(); ++it){
            if(!it->isEmpty()){     // this step to guarantee the root element to settle properly
                nodePtr = nodePtr->getOrAppendChildNode(*it);
            }
        }
        auto newLeaf = nodePtr->setLeaf(leaf);
        checkUrlDuplicateName(newLeaf);
    }
}

void IControllerManage::registerPathValidator(const QString &name, const QString &regexp)
{
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
    auto inst = instance();
    if(inst->m_pathFunValidators.contains(name) || inst->m_pathFunValidators.contains(name)){
        auto info = name + " validator already registered";
        qFatal(info.toUtf8());
    }

    inst->m_pathFunValidators[name] = fun;
}

void IControllerManage::registerPreProcessor(IProcessorWare *middleWare)
{
    auto inst = instance();
    inst->m_preProcessors.append(middleWare);
}

void IControllerManage::registerPostProcessor(IProcessorWare *middleWare)
{
    auto inst = instance();
    inst->m_postProcessors.append(middleWare);
}

void IControllerManage::registerPreInterceptor(IInterceptorWare *middleWare)
{
    auto inst = instance();
    inst->m_preInterceptors.append(middleWare);
}

void IControllerManage::registerPostInterceptor(IInterceptorWare *middleWare)
{
    auto inst = instance();
    inst->m_postInterceptors.append(middleWare);
}

void IControllerManage::travalPrintUrlTree()
{
    instance()->m_urlMapppings->travelPrint();
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

IUrlFunctionNode *IControllerManage::getUrlFunction(IRequest &request)
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

    QVector<IUrlFunctionNode*> nodes =  queryFunctionNodes(nodePtr, fragments, method);
    if(nodes.length() == 0){
        return nullptr;
    }else if(nodes.length() > 1){
        auto info = url + " : " + IHttpMethodHelper::toString(method) + "matched multi-functions, please check";
        qFatal(info.toUtf8());
    }

    auto node = nodes.first();
    request.getRaw()->m_requestUrlParameters = (getPathVariable(node->parentNode, fragments));
    return node;
}

IStatusFunctionNode *IControllerManage::getStatusFunction(IHttpStatus status)
{
    auto inst = instance();
    if(inst->m_statusMappings.contains(status)){
        return &inst->m_statusMappings[status];
    }
    return nullptr;
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
        if(obj->match(request, response)
            && obj->action(request, response)){
            continue;
//            return true;
        }
    }
    return true;
}

bool IControllerManage::postProcess(IRequest &request, IResponse &response)
{
    auto inst = instance();
    for(auto obj : inst->m_postProcessors){
        if(obj->match(request, response)
            && obj->action(request, response)){
            continue;
            //            return true;
        }
    }
    return true;
}

QVector<IUrlFunctionNode *> IControllerManage::queryFunctionNodes(IControllerRouteNode *parentNode,
                                                             const QStringList &fragments, IHttpMethod method)
{
    QVector<IUrlFunctionNode*> ret;
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

bool IControllerManage::checkUrlDuplicateName(const IUrlFunctionNode *node)
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
