#include "IControllerParamBeanUtil.h"

#include "base/IConvertUtil.h"
#include "base/IConstantUtil.h"
#include "base/IToeUtil.h"
#include "core/bean/IBeanWare.h"
#include "core/configuration/IConfigurationManage.h"
#include "web/node/IFunctionNode.h"
#include "web/net/IRequest.h"
#include "web/net/IResponse.h"
#include "web/IWebAst.h"

$PackageWebCoreBegin

$UseAsset(IWebAst)

void* IControllerParamBeanUtil::getParamOfBean(const IFunctionParamNode &node, IRequest &request)
{
    auto ptr = QMetaType::create(node.paramTypeId);
    auto beanWare = static_cast<IBeanWare*>(ptr);
    const auto& paramName = node.paramName;

    // TODO: 这里没有区分 content 和 body 的区别。
//    if((request.method() != IHttpMethod::GET)
//        &&( paramName.endsWith("_content") || paramName.endsWith("_body"))){
//        return assambleBeanWareWithBody(beanWare, request);
//    }

    const auto& suffixes = getParameterSuffix();
    const auto& funs = getParameterFun();
    int len = suffixes.length();
    for(int i=0; i<len; i++){
        if(paramName.endsWith(suffixes[i])){
            return funs[i](beanWare, request);
        }
    }

    return assambleBeanWareWithMixed(beanWare, request);
}

void *IControllerParamBeanUtil::assamleBeanWareWithContent(IBeanWare *bean, IRequest &request)
{
    if(request.method() == IHttpMethod::GET){
        QString info = "can not get any body content when in GET method";
        request.setInvalid(IHttpStatus::BAD_REQUEST_400, info);
        return bean;
    }

    auto mime = request.mime();
    switch (mime) {
    case IHttpMime::APPLICATION_WWW_FORM_URLENCODED:
        return resolveBodyForm(bean, request);
    case IHttpMime::MULTIPART_FORM_DATA:
        return resolveBodyMultiPart(bean, request);
    case IHttpMime::APPLICATION_JSON:
    case IHttpMime::APPLICATION_JSON_UTF8:
        return resolveBodyJson(bean, request);
    case IHttpMime::TEXT_XML:
        return resolveBodyXml(bean, request);
    default:
        request.setInvalid(IHttpStatus::BAD_REQUEST_400, "the request type can not be converted to a bean");
    }
    return bean;
}


void *IControllerParamBeanUtil::assambleBeanWareWithBody(IBeanWare *bean, IRequest &request)
{
    if(request.method() == IHttpMethod::GET){
        QString info = "can not get any body content when in GET method";
        request.setInvalid(IHttpStatus::BAD_REQUEST_400, info);
        return bean;
    }

    // 在 body 当中存在嵌套数据的，目前仅有 Json 和 xml 能够办到
    if(request.mime() == IHttpMime::APPLICATION_JSON
        ||request.mime() == IHttpMime::APPLICATION_JSON_UTF8){
        bool ok;
        const auto& value = request.bodyJson(&ok);
        if(!ok || value.isObject()){
            QString info = "body to jsonobject is not valid";
            request.setInvalid(IHttpStatus::BAD_REQUEST_400, info);
        }

        auto obj = value.toObject();
        if(checkKeyInJsonAndBean(obj, bean, request)){
            bean->load(obj);
        }
        return bean;
    }
    if(request.mime() == IHttpMime::TEXT_XML){
        qFatal("current not support xml");
    }

    QString info = "can not get any part of body in type except json and xml";
    request.setInvalid(IHttpStatus::BAD_REQUEST_400, info);
    return bean;
}

void *IControllerParamBeanUtil::assambleBeanWareWithParameter(IBeanWare *bean, IRequest &request)
{
    const auto& parameters = request.paramParameters();

    if(checkKeyInQByteArrayMap(parameters, bean, request)){
        bool convertOk;
        auto map = resolveBeanFieldAsMap(parameters, bean, request, &convertOk);
        if(convertOk){
            bean->load(map);
        }
    }
    return bean;
}

void *IControllerParamBeanUtil::assambleBeanWareWithUrl(IBeanWare *bean, IRequest &request)
{
    const auto& parameters = request.urlParameters();

    if(checkKeyInQByteArrayMap(parameters, bean, request)){
        bool convertOk;
        auto map = resolveBeanFieldAsMap(parameters, bean, request, &convertOk);
        if(convertOk){
            bean->load(map);
        }
    }
    return bean;
}

void *IControllerParamBeanUtil::assambleBeanWareWithHeaders(IBeanWare *bean, IRequest &request)
{
    const auto& parameters = request.headers();

    if(checkKeyInListPair(parameters, bean, request)){
        bool convertOk;
        auto map = resolveBeanFieldAsMap(parameters, bean, request, &convertOk);
        if(convertOk){
            bean->load(map);
        }
    }
    return bean;
}

void *IControllerParamBeanUtil::assambleBeanWareWithMixed(IBeanWare *bean, IRequest &request)
{
    const auto& props = bean->getMetaProperties();

    QMap<QString, QVariant> map;

    // TODO:

    bool convertOk;
    for(auto prop : props){
        auto value = request.getMixedParameter(prop.name(), &convertOk);
        if(!convertOk){
            if(bean->isIgnorableField(prop.propertyIndex())){
                continue;
            }

            IAssetInfo info;
            info.reason = QString( "bean inner parameter not found. name : ").append(prop.name());
            if(isBeanResoveStrictMode()){
                request.setInvalid(IHttpStatus::BAD_REQUEST_400, info.reason);
                return bean;
            }
            $Ast->warn("assamble_bean_when_bean_inner_parameter_not_found", info);
            continue;
        }

        auto variant = IConvertUtil::toVariant(value, QMetaType::Type(prop.type()), &convertOk);
        if(!convertOk){
            if(bean->isIgnorableField(prop.propertyIndex())){
                continue;
            }
            IAssetInfo info;
            info.reason = QString( "bean inner parameter format not correct. name : ").append(prop.name());
            if(isBeanResoveStrictMode()){
                request.setInvalid(IHttpStatus::BAD_REQUEST_400, info.reason);
                return bean;
            }
            $Ast->warn("assamble_bean_when_bean_inner_parameter_not_found", info);
            continue;
        }
        map[prop.name()] = variant;
    }

    bean->load(map);
    return bean;
}

void *IControllerParamBeanUtil::assambleBeanWareWithCookie(IBeanWare *bean, IRequest &request)
{
    Q_UNUSED(request)

    qFatal(IConstantUtil::UnImplimentedMethod);
    return bean;
}

void *IControllerParamBeanUtil::assambleBeanWareWithSession(IBeanWare *bean, IRequest &request)
{
    Q_UNUSED(request)

    qFatal(IConstantUtil::UnImplimentedMethod);
    return bean;
}

void *IControllerParamBeanUtil::assambleBeanWareWithApplication(IBeanWare *bean, IRequest &request)
{
    Q_UNUSED(request)

    qFatal(IConstantUtil::UnImplimentedMethod);
    return bean;
}

void *IControllerParamBeanUtil::assambleBeanWareWithSystem(IBeanWare *bean, IRequest &request)
{
    Q_UNUSED(request)

    qFatal(IConstantUtil::UnImplimentedMethod);
    return bean;
}

void *IControllerParamBeanUtil::resolveBodyForm(IBeanWare *bean, IRequest &request)
{
    const auto& parameters = request.bodyFormParameters();

    if(checkKeyInQByteArrayMap(parameters, bean, request)){
        bool convertOk;
        auto map = resolveBeanFieldAsMap(parameters, bean, request, &convertOk);
        if(convertOk){
            bean->load(map);
        }
    }
    return bean;
}

void *IControllerParamBeanUtil::resolveBodyMultiPart(IBeanWare *bean, IRequest &request)
{
    const auto& multiparts = request.bodyMultiParts();

    if(checkKeyInMultiPart(multiparts, bean, request)){
        bool convertOk;
        auto map = resolveBeanFieldAsMap(multiparts, bean, request, &convertOk);
        if(convertOk){
            bean->load(map);
        }
    }
    return bean;
}

void *IControllerParamBeanUtil::resolveBodyJson(IBeanWare *bean, IRequest &request)
{
    bool ok;
    auto value = request.bodyJson(&ok);
    if(!ok || !value.isObject()){
        request.setInvalid(IHttpStatus::BAD_REQUEST_400, "json value is not ok");
        return bean;
    }

    auto object = value.toObject();
    if(checkKeyInJsonAndBean(object, bean, request)){
        bean->load(object);
    }
    return bean;
}

void *IControllerParamBeanUtil::resolveBodyXml(IBeanWare *bean, IRequest &request)
{
    // TODO: xml
    request.setInvalid(IHttpStatus::BAD_REQUEST_400, "current convertion to bean can not be done, due to xml type");
    return bean;
}

QMap<QString, QVariant> IControllerParamBeanUtil::resolveBeanFieldAsMap(const QList<QPair<QString, QString> > &list, IBeanWare *bean, IRequest &request, bool *ok)
{
    IToeUtil::setOk(ok, true);
    QMap<QString, QVariant> map;

    bool convertOk;
    auto props = bean->getMetaProperties();
    for(const auto& prop : props){
        QString value;
        for(const auto& pair : list){
            if(pair.first == prop.name()){
                value = pair.second;
            }
        }

        auto variant = IConvertUtil::toVariant(value, QMetaType::Type(prop.type()), &convertOk);
        if(!convertOk){
            if(bean->isIgnorableField(prop.propertyIndex())){
                continue;
            }
            IAssetInfo info;
            info.reason = QString(prop.name()).append(" format not correct");
            if(isBeanResoveStrictMode()){
                IToeUtil::setOk(ok, false);
                request.setInvalid(IHttpStatus::BAD_REQUEST_400, info.reason);
                return map;
            }

            $Ast->warn("assamble_bean_when_bean_inner_parameter_not_found", info);
            continue;
        }

        map[prop.name()] = variant;
    }
    return map;
}

QMap<QString, QVariant> IControllerParamBeanUtil::resolveBeanFieldAsMap(const QMap<QString, QByteArray> &raw
                                                                            , IBeanWare* bean, IRequest& request, bool* ok)
{
    IToeUtil::setOk(ok, true);
    QMap<QString, QVariant> map;

    bool convertOk;
    auto props = bean->getMetaProperties();
    for(const auto& prop : props){
        auto value = raw[prop.name()];
        auto variant = IConvertUtil::toVariant(value, QMetaType::Type(prop.type()), &convertOk);
        if(!convertOk){
            if(bean->isIgnorableField(prop.propertyIndex())){
                continue;
            }
            IAssetInfo info;
            info.reason = QString(prop.name()).append(" format not correct");
            if(isBeanResoveStrictMode()){
                IToeUtil::setOk(ok, false);
                request.setInvalid(IHttpStatus::BAD_REQUEST_400, info.reason);
                return map;
            }
            $Ast->warn("assamble_bean_when_bean_inner_parameter_not_found", info);
            continue;
        }

        map[prop.name()] = variant;
    }
    return map;
}

QMap<QString, QVariant> IControllerParamBeanUtil::resolveBeanFieldAsMap(const QVector<IMultiPart> &parts
                                                                            , IBeanWare* bean, IRequest& request, bool* ok)
{
    QMap<QString, QVariant> map;
    const QStringList& fieldNames = bean->getMetaFieldNames();

    bool convertOk;
    for(const auto& part : parts){
        QString name = part.name;
        if(fieldNames.contains(name)){
            auto value = part.content;
            auto prop = bean->getMetaProperty(name);        // should optimized
            auto variant = IConvertUtil::toVariant(value, QMetaType::Type(prop.type()), &convertOk);
            if(!convertOk){
                if(bean->isIgnorableField(prop.propertyIndex())){
                    continue;
                }
                IAssetInfo info;
                info.reason = QString(prop.name()).append(" format not correct");
                if(isBeanResoveStrictMode()){
                    IToeUtil::setOk(ok, false);
                    request.setInvalid(IHttpStatus::BAD_REQUEST_400, info.reason);
                    return map;
                }

                $Ast->warn("assamble_bean_when_bean_inner_parameter_not_found", info);
                continue;
            }
            map[name] = variant;
        }
    }
    return map;
}

bool IControllerParamBeanUtil::checkKeyInJsonAndBean(const QJsonObject &obj, IBeanWare* bean, IRequest& request)
{
    if(IConstantUtil::ReleaseMode){
        return true;
    }

    auto props = bean->getMetaProperties();
    for(const auto& prop : props){
        if(bean->isIgnorableField(prop.propertyIndex())){        // ignored, check pass
            continue;
        }

        if(!obj.contains(prop.name())){
            IAssetInfo info;
            info.reason = QString("json do not contain pair :").append(prop.name());
            if(isBeanResoveStrictMode()){
                request.setInvalid(IHttpStatus::BAD_REQUEST_400, info.reason);
                return false;

            }
            $Ast->warn("assamble_bean_when_bean_inner_parameter_not_found", info);
        }
    }
    return true;
}

bool IControllerParamBeanUtil::checkKeyInMultiPart(const QVector<IMultiPart> &parts, IBeanWare *bean, IRequest &request)
{
    if(IConstantUtil::ReleaseMode){
        return true;
    }

    QStringList multiPartNames;
    for(const auto& part : parts){
        multiPartNames.append(part.name);
    }

    auto props = bean->getMetaProperties();
    for(auto prop : props){
        if(bean->isIgnorableField(prop.propertyIndex())){
            continue;
        }

        if(!multiPartNames.contains(prop.name())){
            IAssetInfo info;
            info.reason = QString(prop.name()).append(" not found");
            if(isBeanResoveStrictMode()){
                request.setInvalid(IHttpStatus::BAD_REQUEST_400, info.reason);
                return false;
            }
            $Ast->warn("assamble_bean_when_bean_inner_parameter_not_found", info);
            continue;
        }
    }
    return true;
}

bool IControllerParamBeanUtil::checkKeyInQByteArrayMap(const QMap<QString, QByteArray> &map, IBeanWare *bean, IRequest &request)
{
    if(IConstantUtil::ReleaseMode){
        return true;
    }

    QMap<QString, QString> newMap;
    auto keys = map.keys();
    for(auto key : keys){
        newMap[key] = "";
    }
    return checkKeyInQStringMap(newMap, bean, request);
}

bool IControllerParamBeanUtil::checkKeyInListPair(const QList<QPair<QString, QString> > &list, IBeanWare *bean, IRequest &request)
{
    if(IConstantUtil::ReleaseMode){
        return true;
    }

    QMap<QString, QString> newMap;
    for(const auto& pair : list){
        newMap[pair.first] = "";
    }
    return checkKeyInQStringMap(newMap, bean, request);
}

bool IControllerParamBeanUtil::checkKeyInQStringMap(const QMap<QString, QString> &map, IBeanWare *bean, IRequest &request)
{
    if(IConstantUtil::ReleaseMode){
        return true;
    }

    auto props = bean->getMetaProperties();
    for(const auto& prop : props){
        if(bean->isIgnorableField(prop.propertyIndex())){
            continue;
        }

        if(!map.contains(prop.name())){
            IAssetInfo info;
            info.reason = QString(prop.name()).append(" not found");
            if(isBeanResoveStrictMode()){
                request.setInvalid(IHttpStatus::BAD_REQUEST_400, info.reason);
                return false;
            }
            $Ast->warn("assamble_bean_when_bean_inner_parameter_not_found", info);
            continue;
        }
    }
    return true;
}

bool IControllerParamBeanUtil::isBeanResoveStrictMode()
{
    static bool isStrict = true;

    static std::once_flag flag;
    std::call_once(flag, [](){
        bool ok;
        auto value = IConfigurationManage::getSystemValue("BEAN_RESOLVE_IS_STRICT_MODE", &ok);
        if(!ok || !value.isBool()){
            isStrict = true;
        }else{
            isStrict = value.toBool();
        }
    });

    return isStrict;
}

QStringList &IControllerParamBeanUtil::getParameterSuffix()
{
    static QStringList suffix = {
        "_content", "_body",
        "_param", "_url", "_header",
        "_mixed",
        "_cookie", "_session", "_app", "_system"
    };

    return suffix;
}

QVector<IControllerParamBeanUtil::ParamFun>& IControllerParamBeanUtil::getParameterFun()
{
    static QVector<ParamFun> m_paramFuns;
    static std::once_flag flag;
    std::call_once(flag, [](){
        m_paramFuns << IControllerParamBeanUtil::assamleBeanWareWithContent;
        m_paramFuns << IControllerParamBeanUtil::assambleBeanWareWithBody;
        m_paramFuns << IControllerParamBeanUtil::assambleBeanWareWithParameter;
        m_paramFuns << IControllerParamBeanUtil::assambleBeanWareWithUrl;
        m_paramFuns << IControllerParamBeanUtil::assambleBeanWareWithHeaders;

        m_paramFuns << IControllerParamBeanUtil::assambleBeanWareWithMixed;
        m_paramFuns << IControllerParamBeanUtil::assambleBeanWareWithCookie;
        m_paramFuns << IControllerParamBeanUtil::assambleBeanWareWithSession;
        m_paramFuns << IControllerParamBeanUtil::assambleBeanWareWithApplication;
        m_paramFuns << IControllerParamBeanUtil::assambleBeanWareWithSystem;
    });

    return m_paramFuns;
}

$PackageWebCoreEnd
