#include "IHttpControllerParameter.h"

#include "core/base/IJsonUtil.h"
#include "core/base/IToeUtil.h"
#include "core/bean/IBeanWare.h"
#include "core/bean/IBeanTypeManage.h"
#include "core/task/ITaskManage.h"
#include "http/controller/private/IHttpControllerBeanParameter.h"
#include "http/invalid/IHttpBadRequestInvalid.h"
#include "http/jar/IMultiPart.h"
#include "http/node/IMethodNode.h"
#include "http/node/IFunctionNode.h"
#include "http/node/IParamNode.h"
#include "http/net/IRequest.h"
#include "http/net/IResponse.h"
#include "http/net/impl/IRequestRaw.h"
#include "http/response/IResponseInterface.h"
#include "http/response/IResponseManage.h"
#include "http/response/IPlainTextResponse.h"
#include "http/response/IStatusResponse.h"
#include "http/response/IJsonResponse.h"
#include "http/response/IByteArrayResponse.h"
#include "http/IHttpAssert.h"

$PackageWebCoreBegin

$UseAssert(IHttpAssert)

namespace IControllerParameterHelper
{
    static const QString GiveColorSeeSee = QStringLiteral("浪额康康四辣锅削阔爱");
}
using namespace IControllerParameterHelper;

namespace IControllerFunctionBaseImplHelper
{
    void* convertParamToJson(const IParamNode &node, const QByteArray &content, bool& ok);
}

bool IHttpControllerParameter::createArguments(const IMethodNode& methodNode, ParamType& params, IRequest &request)
{
    auto inst = instance();
    for(int i=0; i<=10; i++){
        params[i] = nullptr;
    }

    params[0] = inst->createReturnParam(methodNode.returnTypeId);

    bool ok;
    for(int i=0; i<methodNode.getParamCount(); i++){
        params[i + 1] = inst->createArgParam(methodNode.paramNodes[i], request, ok);
        if(!ok){
            return false;
        }
    }

    return true;
}

void IHttpControllerParameter::destroyArguments(const IMethodNode& node, void **params)
{
    auto inst = instance();
    inst->destroyReturnParam(params[0], node.returnTypeId);

    for(int i=0; i<node.getParamCount(); i++){
        inst->destroyArgParam(node.paramNodes[i], params[i+1]);
    }
}

void IHttpControllerParameter::resolveReturnValue(IResponse& response, const IMethodNode& functionNode, ParamType &params)
{
    QMetaType::Type typeId = functionNode.returnTypeId;
    QSharedPointer<IResponseWare> responseWare;
    auto inst = instance();
    switch (typeId) {
    case QMetaType::Void:
        inst->wrapVoidReturnInstance(response, functionNode, params);
        return;
    case QMetaType::QString:
        responseWare = inst->createStringReturnInstance(params);
        break;
    case QMetaType::Int:
        responseWare = QSharedPointer<IStatusResponse>::create(*static_cast<int*>(params[0]));;
        break;
    case QMetaType::QJsonArray:
        responseWare = QSharedPointer<IJsonResponse>::create(*static_cast<QJsonArray*>(params[0]));
        break;
    case QMetaType::QJsonObject:
        responseWare = QSharedPointer<IJsonResponse>::create(*static_cast<QJsonObject*>(params[0]));
        break;
    case QMetaType::QJsonValue:
        responseWare = QSharedPointer<IJsonResponse>::create(*static_cast<QJsonObject*>(params[0]));
        break;
    case QMetaType::QByteArray:
        responseWare = QSharedPointer<IByteArrayResponse>::create(*static_cast<QByteArray*>(params[0]));
        break;
    case QMetaType::QStringList:
        responseWare = QSharedPointer<IPlainTextResponse>::create(IConvertUtil::toString(*static_cast<QStringList*>(params[0])));
        break;
    default:
        auto type = functionNode.returnTypeName;
        if(type.startsWith("I") && type.endsWith("Response")){
            response.setContent(static_cast<IResponseWare*>(params[0]));
            return;
        }else{
            QString info = type + " not supported, please change the return type!";
            qFatal(info.toUtf8());
        }
    }
    response.setContent(responseWare.data());
}

void *IHttpControllerParameter::createReturnParam(int paramTypeId)
{
    return QMetaType::create(paramTypeId);
}

void *IHttpControllerParameter::createArgParam(const IParamNode& node, IRequest &request, bool& ok)
{
    static QVector<CreateParamFunType> funs = {
        &IHttpControllerParameter::getParamOfSystem,
        &IHttpControllerParameter::getParamOfMultipart,
        &IHttpControllerParameter::getParamOfCookiePart,
        &IHttpControllerParameter::getParamOfPrimitiveType,
        &IHttpControllerParameter::getParamOfStringType,
        &IHttpControllerParameter::getParamOfJsonType,
        &IHttpControllerParameter::getParamOfBean,
    };

    ok = true;
    static int length = m_judgeTypes.length();
    for(int i=0; i<length; i++){
        if(m_judgeTypes[i].contains(node.paramTypeId)){
            return std::mem_fn(funs[i])(this, node, request, ok);
        }
    }

    qFatal("error");
    return nullptr;
}

void IHttpControllerParameter::destroyReturnParam(void *obj, int paramTypeId)
{
    QMetaType::destroy(paramTypeId, obj);
}

void IHttpControllerParameter::destroyArgParam(const IParamNode& node, void *obj)
{
    static QVector<ReleaseParamFunType> funs = {
        &IHttpControllerParameter::releaseParamOfSystem,
        &IHttpControllerParameter::releaseParamOfMultipart,
        &IHttpControllerParameter::releaseParamOfCookiePart,
        &IHttpControllerParameter::releaseParamOfPrimitiveType,
        &IHttpControllerParameter::releaseParamOfStringType,
        &IHttpControllerParameter::releaseParamOfJsonType,
        &IHttpControllerParameter::releaseParamOfBean,
    };

    if(obj == nullptr){
        return;
    }

    static int length = m_judgeTypes.length();
    for(int i=0; i<length; i++){
        if(m_judgeTypes[i].contains(node.paramTypeId)){
            auto val = std::mem_fn(funs[i])(this, node, obj);
            if(val == false){
                qFatal(GiveColorSeeSee.toUtf8());
            }
            return;
        }
    }
    qFatal(GiveColorSeeSee.toUtf8());
}

// "IRequest", "IResponse", "ICookieJar", "IMultiPartJar", "IHeaderJar", "ISessionJar"
void *IHttpControllerParameter::getParamOfSystem(const IParamNode& node, IRequest &request, bool& ok)
{
    Q_UNUSED(ok)
    auto index = m_systemTypes.indexOf(node.paramTypeId);

    switch (index / 3) {
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

void *IHttpControllerParameter::getParamOfMultipart(const IParamNode& node, IRequest &request, bool& ok)
{
    // FIXME:
//    auto& parts = request.getRaw()->m_requestMultiParts;
//    for(auto& part : parts) {
//        if(part.name == node.paramName) {
//            return &part;
//        }
//    }

//    IToeUtil::setOk(ok, false);
//    request.setInvalid(IHttpBadRequestInvalid("multipart content do not have content name " + node.paramName));
    return nullptr;
}

void *IHttpControllerParameter::getParamOfCookiePart(const IParamNode &node, IRequest &request, bool& ok)
{
    // FIXME:
    //    QStringList values = request.getRaw()->m_requestCookieParameters.values(node.paramName);
//    if(values.length() == 1){
//        IToeUtil::setOk(ok, true);
//        return new ICookiePart(node.paramName, values.first());
//    }

//    if(values.length() == 0){
//        request.setInvalid(IHttpBadRequestInvalid("ICookiePart does not have name " + node.paramName));
//    }else if(values.length() > 1){
//        request.setInvalid(IHttpBadRequestInvalid("ICookiePart has more than one key, name: " + node.paramName));
//    }
//    IToeUtil::setOk(ok, false);
    return nullptr;
}

void *IHttpControllerParameter::getParamOfBean(const IParamNode& node, IRequest &request, bool& ok)
{
    Q_UNUSED(ok)
    return IHttpControllerBeanParameter::getParamOfBean(node, request);
}

void *IHttpControllerParameter::getParamOfJsonType(const IParamNode& node, IRequest &request, bool& ok)
{
    // FIXME:
    return nullptr;

    //    const auto& content = node.paramName.endsWith("_content")
//                              ? request.bodyContent() : request.getParameter(node.paramName, ok);
//    if(!ok){
//        request.setInvalid(IHttpBadRequestInvalid("convert to json fail. At " + node.paramTypeName + " " + node.paramName));
//        return nullptr;
//    }

//    auto ptr = IControllerFunctionBaseImplHelper::convertParamToJson(node, content, ok);
//    if(!ok){
//        request.setInvalid(IHttpBadRequestInvalid(node.paramName + " can`t be converted to json type"));
//    }
//    return ptr;
}

void *IHttpControllerParameter::getParamOfPrimitiveType(const IParamNode &node, IRequest &request, bool& ok)
{    
    // FIXME:
    return nullptr;
    /*
    const auto& content = node.paramName.endsWith("_content")
                              ? request.bodyContent() : request.getParameter(node.paramName, ok);

    if(!ok || content.isEmpty()){
        request.setInvalid(IHttpBadRequestInvalid(node.paramName + " is empty to convert to any type"));
        IToeUtil::setOk(ok, false);
        return nullptr;
    }

    const QString& paramName = node.paramName;
    auto param = QMetaType::create(node.paramTypeId);
    switch (node.paramTypeId) {
    case QMetaType::Bool :
        *static_cast<bool*>(param) = IConvertUtil::toBool(QString(content), ok);
        request.setInvalidIf(!ok, IHttpBadRequestInvalid(paramName + " can`t be converted to bool"));
        break;
    case QMetaType::Short:
        *static_cast<short*>(param) = IConvertUtil::toShort(QString(content), ok);
        request.setInvalidIf(!ok, IHttpBadRequestInvalid(paramName + " can`t be converted to short"));
        break;
    case QMetaType::UShort:
        *static_cast<ushort*>(param) = IConvertUtil::toUShort(QString(content), ok);
        request.setInvalidIf(!ok, IHttpBadRequestInvalid(paramName + " can`t be converted to ushort"));
        break;
    case QMetaType::Int:
        *static_cast<int*>(param) = IConvertUtil::toInt(QString(content), ok);
        request.setInvalidIf(!ok, IHttpBadRequestInvalid(paramName + " can`t be converted to int"));
        break;
    case QMetaType::UInt:
        *static_cast<uint*>(param) = IConvertUtil::toUInt(QString(content), ok);
        request.setInvalidIf(!ok, IHttpBadRequestInvalid(paramName + " can`t be converted to UInt"));
        break;
    case QMetaType::Long:
        *static_cast<long*>(param) = IConvertUtil::toLong(QString(content), ok);
        request.setInvalidIf(!ok, IHttpBadRequestInvalid(paramName + " can`t be converted to long"));
        break;
    case QMetaType::ULong:
        *static_cast<ulong*>(param) = IConvertUtil::toULong(QString(content), ok);
        request.setInvalidIf(!ok, IHttpBadRequestInvalid(paramName + " can`t be converted to ulong"));
        break;
    case QMetaType::LongLong:
        *static_cast<qlonglong*>(param) = IConvertUtil::toLongLong(QString(content), ok);
        request.setInvalidIf(!ok, IHttpBadRequestInvalid(paramName + " can`t be converted to LongLong"));
        break;
    case QMetaType::ULongLong:
        *static_cast<qulonglong*>(param) = IConvertUtil::toULongLong(QString(content), ok);
        request.setInvalidIf(!ok, IHttpBadRequestInvalid(paramName + " can`t be converted to ULongLong"));
        break;
    case QMetaType::Float:
        *static_cast<float*>(param) = IConvertUtil::toFloat(QString(content), ok);
        request.setInvalidIf(!ok, IHttpBadRequestInvalid(paramName + " can`t be converted to float"));
        break;
    case QMetaType::Double:
        *static_cast<double*>(param) = IConvertUtil::toDouble(QString(content), ok);
        request.setInvalidIf(!ok, IHttpBadRequestInvalid(paramName + " can`t be converted to double"));
        break;
    }

    return param;
    */
}

void *IHttpControllerParameter::getParamOfStringType(const IParamNode &node, IRequest &request, bool& ok)
{
    // FIXME:

    //    const auto& content = node.paramName.endsWith("_content") ? request.bodyContent()
//                                                  : request.getParameter(node.paramName, ok);
//    if(ok){
//        if(node.paramTypeId == QMetaType::QString){
//            QString value = QString(content);
//            return QMetaType::create(QMetaType::QString, &value);
//        }else if(node.paramTypeId == QMetaType::QByteArray){
//            return QMetaType::create(QMetaType::QByteArray, &content);
//        }
//    }

//    request.setInvalid(IHttpBadRequestInvalid("param of string not exist, name: " + node.paramName));
    return nullptr;
}

bool IHttpControllerParameter::releaseParamOfSystem(const IParamNode& node, void *obj)
{
    Q_UNUSED(node)
    Q_UNUSED(obj)
    return true;
}

bool IHttpControllerParameter::releaseParamOfMultipart(const IParamNode& node, void *obj)
{
    Q_UNUSED(node)
    Q_UNUSED(obj)
    return true;
}

bool IHttpControllerParameter::releaseParamOfCookiePart(const IParamNode &node, void *obj)
{
    Q_UNUSED(node)
    if(obj != nullptr){
        auto part = static_cast<ICookiePart*>(obj);
        delete part;
    }
    return true;
}

bool IHttpControllerParameter::releaseParamOfBean(const IParamNode& node, void *obj)
{
    if(obj != nullptr){
        QMetaType::destroy(node.paramTypeId, obj);
    }
    return true;
}

bool IHttpControllerParameter::releaseParamOfJsonType(const IParamNode& node, void *obj)
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

bool IHttpControllerParameter::releaseParamOfPrimitiveType(const IParamNode &node, void *obj)
{
    if(obj != nullptr){
        QMetaType::destroy(node.paramTypeId, obj);
    }
    return true;
}

bool IHttpControllerParameter::releaseParamOfStringType(const IParamNode &node, void *obj)
{
    if(obj != nullptr){
        QMetaType::destroy(node.paramTypeId, obj);
    }
    return true;
}

void IHttpControllerParameter::wrapVoidReturnInstance(IResponse &response, const IMethodNode &functionNode, ParamType &params)
{
    Q_UNUSED(functionNode)
    Q_UNUSED(params)
    if(response.mime() == IHttpMimeUtil::MIME_UNKNOWN_STRING){
        response.setMime(IHttpMime::TEXT_PLAIN_UTF8);
        $Ast->warn("process_void_return_with_request_not_set_mime_error");
    }
    if(response.status() == IHttpStatusCode::UNKNOWN){
        response.setStatus(IHttpStatusCode::OK_200);
        $Ast->warn("process_void_return_with_request_not_set_status_error");
    }
}

QSharedPointer<IResponseWare> IHttpControllerParameter::createStringReturnInstance(void **params)
{
    static auto responseMange = IResponseManage::instance();
    QSharedPointer<IResponseWare> instance;
    auto value = *static_cast<QString*>(params[0]);
    IResponseWare* response;
    if(value.startsWith("$") && (response = responseMange->convertMatch(value)) != nullptr){
        return response->create(std::move(value)); // TODO: 这里应该使用函数优化掉这个内容
    }

    return QSharedPointer<IPlainTextResponse>::create(std::move(value));
}

// 这个地方应该是拷贝instance, 而不是 放置数据
QSharedPointer<IResponseWare> IHttpControllerParameter::createInterfaceReturnInstance(void **params)
{
    auto value = static_cast<IResponseWare*>(params[0]);
    auto instance = value->create(value);        // TODO: 先解决另外一个问题
//    instance->setInstanceCopy(value);
    return instance;
}

void IHttpControllerParameter::initSystemTypes(){
    static const QStringList SystemTypeNames = {
        "IRequest", "IResponse", "ICookieJar", "IMultiPartJar", "IHeaderJar", "ISessionJar"
    };

    static std::once_flag flag;
    std::call_once(flag, [&](){
        QString nmspace = QString($PackageWebCoreName).append("::");
        for(const auto& name : SystemTypeNames){
            m_systemTypes << QMetaType::type(name.toUtf8());
            m_systemTypes << QMetaType::type((name + "&").toUtf8());
            m_systemTypes << QMetaType::type((nmspace + name).toUtf8());
            m_systemTypes << QMetaType::type((nmspace + name + "&").toUtf8());
        }
    });
}

void IHttpControllerParameter::initMultiPartTypes(){
    static std::once_flag flag;
    std::call_once(flag, [&](){
        QString nmspace = QString($PackageWebCoreName).append("::");
        m_multiPartTypes << QMetaType::type("IMultiPart");
        m_multiPartTypes << QMetaType::type("IMultiPart&");
        m_multiPartTypes << QMetaType::type((nmspace + "IMultiPart").toUtf8());
        m_multiPartTypes << QMetaType::type((nmspace + "IMultiPart&").toUtf8());
    });
}

void IHttpControllerParameter::initCookiePartTypes(){
    static std::once_flag flag;
    std::call_once(flag, [&](){
        QString nmspace = QString($PackageWebCoreName).append("::");
        m_cookiePartTypes << QMetaType::type("ICookiePart");
        m_cookiePartTypes << QMetaType::type("ICookiePart&");
        m_cookiePartTypes << QMetaType::type((nmspace + "ICookiePart").toUtf8());
        m_cookiePartTypes << QMetaType::type((nmspace + "ICookiePart&").toUtf8());
    });
}

void IHttpControllerParameter::initPrimitiveTypes()
{
    m_primitiveTypes = {
        QMetaType::Bool,
        QMetaType::Short, QMetaType::UShort,
        QMetaType::Int, QMetaType::UInt,
        QMetaType::Long, QMetaType::ULong,
        QMetaType::LongLong, QMetaType::ULongLong,
        QMetaType::Float, QMetaType::Double
    };

    m_jsonTypes = {
        QMetaType::QJsonValue,
        QMetaType::QJsonArray,
        QMetaType::QJsonObject
    };

    m_stringTypes = {
        QMetaType::QString,
        QMetaType::QByteArray
    };
}

void IHttpControllerParameter::initBeanTypes(){
    static std::once_flag flag;
    std::call_once(flag, [&](){
        for(int id=QMetaType::User; ; id++){
            QString name = QMetaType::typeName(id);
            if(name.isEmpty()){
                break;
            }
            if(IBeanTypeManage::containBean(name)){
                m_beanTypes << id;
            }
        }
    });
}

void* IControllerFunctionBaseImplHelper::convertParamToJson(const IParamNode &node, const QByteArray &content, bool& ok)
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

void IHttpControllerParameter::task()
{
    initPrimitiveTypes();
    initSystemTypes();
    initMultiPartTypes();
    initCookiePartTypes();
    initBeanTypes();

    static std::once_flag flag;
    std::call_once(flag, [&](){
        m_judgeTypes << m_systemTypes;
        m_judgeTypes << m_multiPartTypes;
        m_judgeTypes << m_cookiePartTypes;
        m_judgeTypes << m_primitiveTypes;
        m_judgeTypes << m_stringTypes;
        m_judgeTypes << m_jsonTypes;
        m_judgeTypes << m_beanTypes;
    });
}

$PackageWebCoreEnd
