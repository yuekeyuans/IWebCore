#include "IControllerParamUtil.h"

#include "base/IJsonUtil.h"
#include "base/IToeUtil.h"
#include "core/bean/IBeanWare.h"
#include "core/bean/ITypeManage.h"
#include "core/task/ITaskManage.h"
#include "web/controller/private/IControllerParamBeanUtil.h"
#include "web/node/IMethodNode.h"
#include "web/node/IFunctionNode.h"
#include "web/node/IParamNode.h"
#include "web/net/IMultiPart.h"
#include "web/net/IRequest.h"
#include "web/net/IResponse.h"
#include "web/response/IResponseInterface.h"
#include "web/response/IResponseManage.h"
#include "web/response/IPlainTextResponse.h"
#include "web/response/IStatusCodeResponse.h"
#include "web/response/IJsonResponse.h"
#include "web/response/IByteArrayResponse.h"
#include "web/net/impl/IReqRespRaw.h"
#include "web/IWebAssert.h"

$PackageWebCoreBegin

$UseAssert(IWebAssert)

// show me something that should not be wrong
static const QString GiveColorSeeSee = QStringLiteral("浪额康康四辣锅削阔爱");

static QVector<int> SystemTypes;
static QVector<int> MultiPartTypes;
static QVector<int> CookiePartTypes;
static QVector<int> BeanTypes;
static QVector<QVector<int>> JudgeTypes;

static const QVector<int> PrimitiveTypes = {
    QMetaType::Bool,
    QMetaType::Short, QMetaType::UShort,
    QMetaType::Int, QMetaType::UInt,
    QMetaType::Long, QMetaType::ULong,
    QMetaType::LongLong, QMetaType::ULongLong,
    QMetaType::Float, QMetaType::Double
};

static const QVector<int> JsonTypes = {
    QMetaType::QJsonValue,
    QMetaType::QJsonArray,
    QMetaType::QJsonObject
};

static const QVector<int> StringTypes = {
    QMetaType::QString,
    QMetaType::QByteArray
};

namespace IControllerFunctionBaseImplHelper
{
    void* convertParamToJson(const IParamNode &node, const QByteArray &content, bool* ok);
}

bool IControllerParamUtil::createArguments(const IMethodNode& methodNode, ParamType& params, IRequest &request)
{
    for(int i=0; i<=10; i++){
        params[i] = nullptr;
    }

    params[0] = createReturnParam(methodNode.returnTypeId);

    bool ok;
    for(int i=0; i<methodNode.getParamCount(); i++){
        params[i + 1] = createArgParam(methodNode.paramNodes[i], request, ok);
        if(!ok){
            return false;
        }
    }

    return true;
}

void IControllerParamUtil::destroyArguments(const IMethodNode& node, void **params)
{
    destroyReturnParam(params[0], node.returnTypeId);

    for(int i=0; i<node.getParamCount(); i++){
        destroyArgParam(node.paramNodes[i], params[i+1]);
    }
}

void IControllerParamUtil::resolveReturnValue(IResponse& response, const IMethodNode& functionNode, ParamType &params)
{
    QMetaType::Type typeId = functionNode.returnTypeId;
    QSharedPointer<IResponseWare> instance;

    switch (typeId) {
    case QMetaType::Type::Void:
        wrapVoidReturnInstance(response, functionNode, params);
        return;
    case QMetaType::QString:
        instance = createStringReturnInstance(params);
        break;
    case QMetaType::Int:
        instance = createIntReturnInstance(params);
        break;
    case QMetaType::QJsonArray:
        instance = createJsonArrayReturnInstance(params);
        break;
    case QMetaType::QJsonObject:
        instance = createJsonObjectReturnInstance(params);
        break;
    case QMetaType::QJsonValue:
        instance = createJsonValueReturnInstance(params);
        break;
    case QMetaType::QByteArray:
        instance = createByteArrayReturnInstance(params);
        break;
    case QMetaType::Type::QStringList:
        instance = createStringListReturnType(params);
        break;
    default:
        auto type = functionNode.returnTypeName;
        if(type.startsWith("I") && type.endsWith("Response")){
            instance = createInterfaceReturnInstance(params);
        }else{
            QString info = type + " not supported, please change the return type!";
            qFatal(info.toUtf8());
        }
    }
    response.setContent(instance.data());
}

void *IControllerParamUtil::createReturnParam(int paramTypeId)
{
    return QMetaType::create(paramTypeId);
}

void *IControllerParamUtil::createArgParam(const IParamNode& node, IRequest &request, bool& ok)
{
    static QVector<CreateParamFunType> funs = {
        &IControllerParamUtil::getParamOfSystem,
        &IControllerParamUtil::getParamOfMultipart,
        &IControllerParamUtil::getParamOfCookiePart,
        &IControllerParamUtil::getParamOfPrimitiveType,
        &IControllerParamUtil::getParamOfStringType,
        &IControllerParamUtil::getParamOfJsonType,
        &IControllerParamUtil::getParamOfBean,
    };

    IToeUtil::setOk(ok, true);
    static int length = JudgeTypes.length();
    for(int i=0; i<length; i++){
        if(JudgeTypes[i].contains(node.paramTypeId)){
            return funs[i](node, request, ok);
        }
    }

    qFatal("error");
    return nullptr;
}

void IControllerParamUtil::destroyReturnParam(void *obj, int paramTypeId)
{
    QMetaType::destroy(paramTypeId, obj);
}

void IControllerParamUtil::destroyArgParam(const IParamNode& node, void *obj)
{
    static QVector<ReleaseParamFunType> funs = {
        &IControllerParamUtil::releaseParamOfSystem,
        &IControllerParamUtil::releaseParamOfMultipart,
        &IControllerParamUtil::releaseParamOfCookiePart,
        &IControllerParamUtil::releaseParamOfPrimitiveType,
        &IControllerParamUtil::releaseParamOfStringType,
        &IControllerParamUtil::releaseParamOfJsonType,
        &IControllerParamUtil::releaseParamOfBean,
    };

    if(obj == nullptr){
        return;
    }

    static int length = JudgeTypes.length();
    for(int i=0; i<length; i++){
        if(JudgeTypes[i].contains(node.paramTypeId)){
            auto val = funs[i](node, obj);
            if(val == false){
                qFatal(GiveColorSeeSee.toUtf8());
            }
            return;
        }
    }
    qFatal(GiveColorSeeSee.toUtf8());
}

// "IRequest", "IResponse", "ICookieJar", "IMultiPartJar", "IHeaderJar", "ISessionJar"
void *IControllerParamUtil::getParamOfSystem(const IParamNode& node, IRequest &request, bool& ok)
{
    Q_UNUSED(ok)
    auto index = SystemTypes.indexOf(node.paramTypeId);

    switch (index / 2) {
    case 0:
        return &request;
    case 1:
        return request.response();
    case 2:
        return request.cookieJar();
    case 3:
        return request.multiPartJar();
    case 4:
        return request.headerJar();
    case 5:
        return request.sessionJar();
    default:
        qFatal("error");
    }
    return nullptr;
}

void *IControllerParamUtil::getParamOfMultipart(const IParamNode& node, IRequest &request, bool& ok)
{
    auto& parts = request.getRaw()->m_requestMultiParts;
    for(auto& part : parts) {
        if(part.name == node.paramName) {
            return &part;
        }
    }

    IToeUtil::setOk(ok, false);
    request.setInvalid(IHttpStatus::BAD_REQUEST_400, "multipart content do not have content name " + node.paramName);
    return nullptr;
}

void *IControllerParamUtil::getParamOfCookiePart(const IParamNode &node, IRequest &request, bool& ok)
{
    ICookiePart* part{nullptr};

    int count {0};
    const auto& cookies = request.getRaw()->m_requestCookieParameters;
    for(const auto& cookie : cookies){
        if(cookie.first == node.paramName){
            if(count == 0){
                part = new ICookiePart(cookie.first, cookie.second);
            }
            count ++;
        }
    }

    if(count == 1){
        return part;
    }

    if(count == 0){
        request.setInvalid(IHttpStatus::BAD_REQUEST_400, "ICookiePart does not have name " + node.paramName);
    }else if(count > 1){
        delete part;
        request.setInvalid(IHttpStatus::BAD_REQUEST_400, "ICookiePart has more than one key, name: " + node.paramName);
    }
    IToeUtil::setOk(ok, false);
    return nullptr;
}

void *IControllerParamUtil::getParamOfBean(const IParamNode& node, IRequest &request, bool& ok)
{
    Q_UNUSED(ok)
    return IControllerParamBeanUtil::getParamOfBean(node, request);
}

void *IControllerParamUtil::getParamOfJsonType(const IParamNode& node, IRequest &request, bool& ok)
{
    const auto& content = node.paramName.endsWith("_content")
                              ? request.bodyContent() : request.getParameter(node.paramName, &ok);
    if(!ok){
        request.setInvalid(IHttpStatus::BAD_REQUEST_400, "convert to json fail. At " + node.paramTypeName + " " + node.paramName);
        return nullptr;
    }

    auto ptr = IControllerFunctionBaseImplHelper::convertParamToJson(node, content, &ok);
    if(!ok){
        request.setInvalidIf(!ok, IHttpStatus::BAD_REQUEST_400, node.paramName + " can`t be converted to json type");
    }
    return ptr;
}

void *IControllerParamUtil::getParamOfPrimitiveType(const IParamNode &node, IRequest &request, bool& ok)
{    
    const auto& content = node.paramName.endsWith("_content")
                              ? request.bodyContent() : request.getParameter(node.paramName, &ok);

    if(!ok || content.isEmpty()){
        request.setInvalid(IHttpStatus::BAD_REQUEST_400, node.paramName + " is empty to convert to any type");
        IToeUtil::setOk(ok, false);
        return nullptr;
    }

    const QString& paramName = node.paramName;
    auto param = QMetaType::create(node.paramTypeId);
    switch (node.paramTypeId) {
    case QMetaType::Bool :
        *static_cast<bool*>(param) = IConvertUtil::toBool(QString(content), &ok);
        request.setInvalidIf(!ok, IHttpStatus::BAD_REQUEST_400, paramName + " can`t be converted to bool");
        break;
    case QMetaType::Short:
        *static_cast<short*>(param) = IConvertUtil::toShort(content, &ok);
        request.setInvalidIf(!ok, IHttpStatus::BAD_REQUEST_400, paramName + " can`t be converted to short");
        break;
    case QMetaType::UShort:
        *static_cast<ushort*>(param) = IConvertUtil::toUShort(content, &ok);
        request.setInvalidIf(!ok, IHttpStatus::BAD_REQUEST_400, paramName + " can`t be converted to ushort");
        break;
    case QMetaType::Int:
        *static_cast<int*>(param) = IConvertUtil::toInt(content, &ok);
        request.setInvalidIf(!ok, IHttpStatus::BAD_REQUEST_400, paramName + " can`t be converted to int");
        break;
    case QMetaType::UInt:
        *static_cast<uint*>(param) = IConvertUtil::toUInt(content, &ok);
        request.setInvalidIf(!ok, IHttpStatus::BAD_REQUEST_400, paramName + " can`t be converted to UInt");
        break;
    case QMetaType::Long:
        *static_cast<long*>(param) = IConvertUtil::toLong(content, &ok);
        request.setInvalidIf(!ok, IHttpStatus::BAD_REQUEST_400, paramName + " can`t be converted to long");
        break;
    case QMetaType::ULong:
        *static_cast<ulong*>(param) = IConvertUtil::toULong(content, &ok);
        request.setInvalidIf(!ok, IHttpStatus::BAD_REQUEST_400, paramName + " can`t be converted to ulong");
        break;
    case QMetaType::LongLong:
        *static_cast<qlonglong*>(param) = IConvertUtil::toLongLong(content, &ok);
        request.setInvalidIf(!ok, IHttpStatus::BAD_REQUEST_400, paramName + " can`t be converted to LongLong");
        break;
    case QMetaType::ULongLong:
        *static_cast<qulonglong*>(param) = IConvertUtil::toULongLong(content, &ok);
        request.setInvalidIf(!ok, IHttpStatus::BAD_REQUEST_400, paramName + " can`t be converted to ULongLong");
        break;
    case QMetaType::Float:
        *static_cast<float*>(param) = IConvertUtil::toFloat(content, &ok);
        request.setInvalidIf(!ok, IHttpStatus::BAD_REQUEST_400, paramName + " can`t be converted to float");
        break;
    case QMetaType::Double:
        *static_cast<double*>(param) = IConvertUtil::toDouble(content, &ok);
        request.setInvalidIf(!ok, IHttpStatus::BAD_REQUEST_400, paramName + " can`t be converted to double");
        break;
    }

    return param;
}

void *IControllerParamUtil::getParamOfStringType(const IParamNode &node, IRequest &request, bool& ok)
{
    const auto& content = node.paramName.endsWith("_content") ? request.bodyContent()
                                                  : request.getParameter(node.paramName, &ok);

    if(ok){
        if(node.paramTypeId == QMetaType::QString){
            QString value = QString(content);
            return QMetaType::create(QMetaType::QString, &value);
        }else if(node.paramTypeId == QMetaType::QByteArray){
            return QMetaType::create(QMetaType::QByteArray, &content);
        }
    }

    request.setInvalid(IHttpStatus::BAD_REQUEST_400, "param of string not exist, name: " + node.paramName);
    return nullptr;
}

constexpr bool IControllerParamUtil::releaseParamOfSystem(const IParamNode& node, void *obj)
{
    Q_UNUSED(node)
    Q_UNUSED(obj)
    return true;
}

constexpr bool IControllerParamUtil::releaseParamOfMultipart(const IParamNode& node, void *obj)
{
    Q_UNUSED(node)
    Q_UNUSED(obj)
    return true;
}

bool IControllerParamUtil::releaseParamOfCookiePart(const IParamNode &node, void *obj)
{
    Q_UNUSED(node)
    if(obj != nullptr){
        auto part = static_cast<ICookiePart*>(obj);
        delete part;
    }
    return true;
}

bool IControllerParamUtil::releaseParamOfBean(const IParamNode& node, void *obj)
{
    if(obj != nullptr){
        QMetaType::destroy(node.paramTypeId, obj);
    }
    return true;
}

bool IControllerParamUtil::releaseParamOfJsonType(const IParamNode& node, void *obj)
{
    Q_UNUSED(obj)
    if(obj != nullptr){
        auto id = node.paramTypeId;
        if(id != QMetaType::QJsonValue){
            QMetaType::destroy(id, obj);
        }
    }
    return true;
}

bool IControllerParamUtil::releaseParamOfPrimitiveType(const IParamNode &node, void *obj)
{
    if(obj != nullptr){
        QMetaType::destroy(node.paramTypeId, obj);
    }
    return true;
}

bool IControllerParamUtil::releaseParamOfStringType(const IParamNode &node, void *obj)
{
    if(obj != nullptr){
        QMetaType::destroy(node.paramTypeId, obj);
    }
    return true;
}

void IControllerParamUtil::wrapVoidReturnInstance(IResponse &response, const IMethodNode &functionNode, ParamType &params)
{
    Q_UNUSED(functionNode)
    Q_UNUSED(params)
    if(response.mime() == IHttpMimeHelper::MIME_UNKNOWN_STRING){
        response.setMime(IHttpMime::TEXT_PLAIN_UTF8);
        $Ast->warn("process_void_return_with_request_not_set_mime_error");
    }
    if(response.status() == IHttpStatus::UNKNOWN){
        response.setStatus(IHttpStatus::OK_200);
        $Ast->warn("process_void_return_with_request_not_set_status_error");
    }
}

QSharedPointer<IResponseWare> IControllerParamUtil::createStringReturnInstance(void **params)
{
    QSharedPointer<IResponseWare> instance;
    auto value = *static_cast<QString*>(params[0]);
    IResponseWare* response;
    if(value.startsWith("$") && (response = IResponseManage::convertMatch(value)) != nullptr){
        instance = response->createInstance();
    }else{
        instance = IPlainTextResponse::createIPlainTexInstance();
    }
    instance->setInstanceArg(std::move(value)); // 这一个是使用 QString 传入参数，其他的全部使用 void* 传入
    return instance;
}

QSharedPointer<IResponseWare> IControllerParamUtil::createIntReturnInstance(void **params)
{
    auto instance = IStatusCodeResponse::createStatusCodeInstance();
    instance->setInstanceArg(params[0]);
    return instance;
}

QSharedPointer<IResponseWare> IControllerParamUtil::createJsonValueReturnInstance(void **params)
{
    static const QString suffix = "QJsonValue";
    auto instance = IJsonResponse::createJsonInstance();
    instance->setInstanceArg(params[0], suffix);
    return instance;
}

QSharedPointer<IResponseWare> IControllerParamUtil::createJsonObjectReturnInstance(void **params)
{
    static const QString suffix = "QJsonObject";
    auto instance = IJsonResponse::createJsonInstance();
    instance->setInstanceArg(params[0], suffix);
    return instance;
}

QSharedPointer<IResponseWare> IControllerParamUtil::createJsonArrayReturnInstance(void **params)
{
    static const QString suffix = "QJsonArray";
    auto instance = IJsonResponse::createJsonInstance();
    instance->setInstanceArg(params[0], suffix);
    return instance;
}

QSharedPointer<IResponseWare> IControllerParamUtil::createByteArrayReturnInstance(void **params)
{
    auto instance = IByteArrayResponse::createByteArrayInstance();
    instance->setInstanceArg(params[0]);
    return instance;
}

QSharedPointer<IResponseWare> IControllerParamUtil::createStringListReturnType(void **params)
{
    auto value = static_cast<QStringList*>(params[0]);
    auto string = IConvertUtil::toString(*value);
    auto instance = IPlainTextResponse::createIPlainTexInstance();
    instance->setInstanceArg(std::move(string));
    return instance;
}

// 这个地方应该是拷贝instance, 而不是 放置数据
QSharedPointer<IResponseWare> IControllerParamUtil::createInterfaceReturnInstance(void **params)
{
    auto value = static_cast<IResponseWare*>(params[0]);
    auto instance = value->createInstance();
    instance->setInstanceCopy(value);
    return instance;
}


void IControllerParamUtil::initSystemTypes(){
    static const QStringList SystemTypeNames = {
        "IRequest", "IResponse", "ICookieJar", "IMultiPartJar", "IHeaderJar", "ISessionJar"
    };

    static std::once_flag flag;
    std::call_once(flag, [](){
        QString nmspace = QString($PackageWebCoreName).append("::");

        for(const auto& name : SystemTypeNames){
            SystemTypes << QMetaType::type((nmspace + name).toUtf8());
            SystemTypes << QMetaType::type((nmspace + name + "&").toUtf8());
        }
    });
}

void IControllerParamUtil::initMultiPartTypes(){
    static std::once_flag flag;
    std::call_once(flag, [](){
//        QString nmspace = QString($PackageWebCoreName).append("::");
        const QString nmspace = "";
        MultiPartTypes << QMetaType::type((nmspace + "IMultiPart").toUtf8());
        MultiPartTypes << QMetaType::type((nmspace + "IMultiPart&").toUtf8());
        qDebug() << MultiPartTypes;
    });
}

void IControllerParamUtil::initCookiePartTypes(){
    static std::once_flag flag;
    std::call_once(flag, [](){
//        QString nmspace = QString($PackageWebCoreName).append("::");
        const QString nmspace = "";
        CookiePartTypes << QMetaType::type((nmspace + "ICookiePart").toUtf8());
        CookiePartTypes << QMetaType::type((nmspace + "ICookiePart&").toUtf8());
    });
}

void IControllerParamUtil::initBeanTypes(){
    static std::once_flag flag;
    std::call_once(flag, [](){
        for(int id=QMetaType::User; ; id++){
            QString name = QMetaType::typeName(id);
            if(name.isEmpty()){
                break;
            }
            if(IBeanTypeManage::containBean(name)){
                BeanTypes << id;
            }
        }
    });
}

void IControllerParamUtil::initJudgeTypes(){
    static std::once_flag flag;
    std::call_once(flag, [](){
        JudgeTypes << SystemTypes;
        JudgeTypes << MultiPartTypes;
        JudgeTypes << CookiePartTypes;
        JudgeTypes << PrimitiveTypes;
        JudgeTypes << StringTypes;
        JudgeTypes << JsonTypes;
        JudgeTypes << BeanTypes;
    });
}

void* IControllerFunctionBaseImplHelper::convertParamToJson(const IParamNode &node, const QByteArray &content, bool* ok)
{
    IToeUtil::setOk(ok, true);
    auto param = QMetaType::create(node.paramTypeId);
    switch (node.paramTypeId) {
    case QMetaType::QJsonArray:
        *static_cast<QJsonArray*>(param) = IConvertUtil::toJsonArray(content, ok);
        break;
    case QMetaType::QJsonObject:
        *static_cast<QJsonObject*>(param) = IConvertUtil::toJsonObject(content, ok);
        break;
    case QMetaType::QJsonValue:
        *static_cast<QJsonValue*>(param) = IConvertUtil::toJsonValue(QString(content), ok);
        break;
    }
    return param;
}

void IControllerParamUtil::task()
{
    IControllerParamUtil::initSystemTypes();
    IControllerParamUtil::initMultiPartTypes();
    IControllerParamUtil::initCookiePartTypes();
    IControllerParamUtil::initBeanTypes();
    IControllerParamUtil::initJudgeTypes();
}

$PackageWebCoreEnd
