﻿#include "IArgumentTypeDetail.h"
#include "core/util/ISpawnUtil.h"
#include "core/util/IConstantUtil.h"
#include "core/bean/IBeanTypeManage.h"
#include "http/controller/IHttpControllerAbort.h"
#include "http/controller/IHttpControllerAction.h"
#include "http/IHttpManage.h"
#include "http/invalid/IHttpInternalErrorInvalid.h"
#include "http/invalid/IHttpBadRequestInvalid.h"
#include "http/IRequest.h"
#include "http/IResponse.h"
#include "http/ICookieJar.h"
#include "http/ISessionJar.h"
#include "http/IMultiPartJar.h"
#include "http/IHeaderJar.h"
#include "http/detail/IRequestImpl.h"

$PackageWebCoreBegin

namespace detail
{
    static bool isMultipleType(QMetaType::Type typeId, const IString& typeName)
    {
        if(typeId == QMetaType::QStringList){
            return true;
        }
        if(typeName == "QList<IString>"){
            return true;
        }
        return false;
    }

    static bool isTypeConvertable(QMetaType::Type typeId, const IString& typeName)
    {
        static QList<QMetaType::Type> types = {
            QMetaType::Bool, QMetaType::SChar, QMetaType::UChar,
            QMetaType::UShort, QMetaType::Short, QMetaType::Int, QMetaType::UInt,
            QMetaType::ULong, QMetaType::Long, QMetaType::ULongLong, QMetaType::LongLong,
            QMetaType::Float, QMetaType::Double, QMetaType::QString, QMetaType::QByteArray,
        };
        static QList<IString> typeNames = {
            "IString", "std::string", "IStringView", "QList<IString>", "QStringList",
            "IMultiPart", "ICookiePart"
        };
        return types.contains(typeId) || typeNames.contains(typeName);
    }

    static void* convertPtr(const QList<IString>& data, QMetaType::Type typeId, const IString& typeName)
    {
        if(typeId == QMetaType::QStringList){
            auto ret = new QStringList;
            for(const auto& val : data){
                ret->append(val.toQString());
            }
            return ret;
        }
        if(typeName == "QList<IString>") {
            return new QList<IString>(data);
        }
        qFatal("not supported");
        return nullptr;
    }

    static void* convertPtr(const IStringViewList& data, QMetaType::Type typeId, const IString& typeName)
    {
        if(typeId == QMetaType::QStringList){
            auto ret = new QStringList;
            for(const auto& val : data){
                ret->append(val.toQString());
            }
            return ret;
        }
        if(typeName == "QList<IString>") {
            auto ret = new QList<IString> ;
            for(auto value : data){
                ret->append(value);
            }
            return ret;
        }
        qFatal("not supported");
        return nullptr;
    }

    static void* convertPtr(const IString& data, QMetaType::Type typeId, const IString& typeName)
    {
        switch (typeId) {
        case QMetaType::Bool:
            return data.valuePtr<bool>();
        case QMetaType::SChar:
            return data.valuePtr<signed char>();
        case QMetaType::UChar:
            return data.valuePtr<unsigned char>();
        case QMetaType::Short:
            return data.valuePtr<signed short>();
        case QMetaType::UShort:
            return data.valuePtr<unsigned short>();
        case QMetaType::Int:
            return data.valuePtr<signed int>();
        case QMetaType::UInt:
            return data.valuePtr<unsigned int>();
        case QMetaType::Long:
            return data.valuePtr<signed long>();
        case QMetaType::ULong:
            return data.valuePtr<unsigned long>();
        case QMetaType::LongLong:
            return data.valuePtr<signed long long>();
        case QMetaType::ULongLong:
            return data.valuePtr<unsigned long long>();
        case QMetaType::Float:
            return data.valuePtr<float>();
        case QMetaType::Double:
            return data.valuePtr<double>();
        case QMetaType::QString:
            return data.valuePtr<QString>();
        case QMetaType::QByteArray:
            return data.valuePtr<QByteArray>();
        default:
            break;
        }
        if(typeName == "IString"){
            return data.valuePtr<IString>();
        }else if(typeName == "std::string"){
            return data.valuePtr<std::string>();
        }else if(typeName == "IStringView"){
            return data.valuePtr<IStringView>();
        }else if(typeName == "IMultiPart"){
            if(!data.isEmpty()){
                qFatal("in multiPart, no optional variable needed");
            }
            return const_cast<IMultiPart*>(&IMultiPart::Empty);
        }else if(typeName == "ICookiePart"){
            if(!data.isEmpty()){
                qFatal("in cookiepart, no optional variable needed");
            }
            return const_cast<ICookiePart*>(&ICookiePart::Empty);
        }
        qFatal("not supported type");
        return nullptr;
    }

    static void deletePtr(void* ptr, QMetaType::Type typeId, const IString& typeName)
    {
        if(!ptr){
            return;
        }
        switch (typeId) {
        case QMetaType::Bool:
            return delete static_cast<bool*>(ptr);
        case QMetaType::SChar:
            return delete static_cast<signed char*>(ptr);
        case QMetaType::UChar:
            return delete static_cast<unsigned char*>(ptr);
        case QMetaType::Short:
            return delete static_cast<short*>(ptr);
        case QMetaType::UShort:
            return delete static_cast<unsigned short*>(ptr);
        case QMetaType::Int:
            return delete static_cast<int*>(ptr);
        case QMetaType::UInt:
            return delete static_cast<unsigned int*>(ptr);
        case QMetaType::Long:
            return delete static_cast<long*>(ptr);
        case QMetaType::ULong:
            return delete static_cast<unsigned long*>(ptr);
        case QMetaType::LongLong:
            return delete static_cast<long long*>(ptr);
        case QMetaType::ULongLong:
            return delete static_cast<unsigned long long*>(ptr);
        case QMetaType::Float:
            return delete static_cast<float*>(ptr);
        case QMetaType::Double:
            return delete static_cast<double*>(ptr);
        case QMetaType::QString:
            return delete static_cast<QString*>(ptr);
        case QMetaType::QByteArray:
            return delete static_cast<QByteArray*>(ptr);
        case QMetaType::QStringList:
            return delete static_cast<QStringList*>(ptr);
        default:
            break;
        }
        if(typeName == "IString"){
            return delete static_cast<IString*>(ptr);
        }else if(typeName == "std::string"){
            return delete static_cast<std::string*>(ptr);
        }else if(typeName == "IStringView"){
            return delete static_cast<IStringView*>(ptr);
        }else if(typeName == "QList<IString>"){
            return delete static_cast<QList<IString>*>(ptr);
        }
        qFatal("error");
    }

}

IArgumentTypeDetail::IArgumentTypeDetail(int typeId, QByteArray paramTypeName, QByteArray nameRaw)
    : IArgumentType()
{
    m_typeId = QMetaType::Type(typeId);
    m_typeName = std::move(paramTypeName);
    m_nameRaw = std::move(nameRaw);
    resolveName();

    static QList<decltype(&IArgumentTypeDetail::createBasicTypes)> funs = {
        &IArgumentTypeDetail::createBasicTypes,
        &IArgumentTypeDetail::createPartTypes,
        &IArgumentTypeDetail::createDecorateTypes,
        &IArgumentTypeDetail::createBeanTypes,
    };
    for(auto fun : funs){
        std::invoke(fun, this);
        if(m_createFun){
            return;
        };
    }
    qFatal("create argument parse failed");
}

void IArgumentTypeDetail::resolveName()
{
    static const QVector<IString> PREFIXES = {
        "auto", "PATH", "QUERY", "HEADER", "COOKIE", "SESSION", "BODY", "FORM", "JSON"
    };
    if(m_nameRaw.isEmpty()){
        qFatal("Name should not be empty");
    }

    IStringViewList args = m_nameRaw.split("_$");
    m_name = args.first();
    args.pop_front();

    for(IStringView arg : args){
        auto index = PREFIXES.indexOf(arg);
        if(index > 0){
            if(m_position > 0){
                qFatal("two more restrict");
            }
            m_position = Position(index);
        }

        // optional
        if(arg.startWith("OPTIONAL")){
            if(m_optional == true){
                qFatal("two more optional");
            }
            m_optional = true;
            auto spliter = arg.find("$$");
            if(spliter != std::string_view::npos){
                m_optionalString = arg.substr(spliter+2);
            }
            if(detail::isTypeConvertable(m_typeId, m_typeName)){
                m_optionalPtr = detail::convertPtr(m_optionalString, m_typeId, m_typeName);
                if(!m_optionalPtr){
                    qFatal("optional can not be converted");
                }
            }else{
                qFatal("optional not convertable");
            }
        }
    }
}

void IArgumentTypeDetail::createBasicTypes()
{
    static QList<decltype(&IArgumentTypeDetail::createRequestType)> funs = {
        &IArgumentTypeDetail::createRequestType,
        &IArgumentTypeDetail::createResponseType,
        &IArgumentTypeDetail::createMultiPartJarType,
        &IArgumentTypeDetail::createCookieJarType,
        &IArgumentTypeDetail::createSessionJarType,
        &IArgumentTypeDetail::createHeaderJarType,
    };

    if(this->m_typeId != QMetaType::UnknownType){
        return;
    }

    for(auto fun : funs){
        std::invoke(fun, this);
        if(m_createFun){
            if(m_optional){
                qFatal("optional can not be exist here");
            }
            if(m_position != Position::Auto){
                qFatal("position should be empty");
            }
            return;
        }
    }
}

void IArgumentTypeDetail::createRequestType()
{
    static const auto types = makeTypes("IRequest");
    if(types.contains(this->m_typeName)){
        this->m_createFun = [](IRequest& request)->void*{
            return &request;
        };
    }
}

void IArgumentTypeDetail::createResponseType()
{
    static const auto types = makeTypes("IResponse");
    if(types.contains(this->m_typeName)){
        this->m_createFun = [](IRequest& request)->void*{
            return new IResponse(request);
        };
        this->m_destroyFun = [](void* ptr){
            return delete static_cast<IResponse*>(ptr);
        };
    }
}

void IArgumentTypeDetail::createMultiPartJarType()
{
    static const auto types = makeTypes("IMultiPartJar");
    if(types.contains(this->m_typeName)){
        this->m_createFun = [](IRequest& request)->void*{
            return &(request.impl().m_multiPartJar);
        };
    }
}

void IArgumentTypeDetail::createSessionJarType()
{
    static const auto types = makeTypes("ISessionJar");
    if(types.contains(this->m_typeName)){
        this->m_createFun = [](IRequest& request)->void*{
            return &(request.impl().m_sessionJar);
        };
    }
}

void IArgumentTypeDetail::createCookieJarType()
{
    static const auto types = makeTypes("ICookieJar");
    if(types.contains(this->m_typeName)){
        this->m_createFun = [](IRequest& request)->void*{
            return &(request.impl().m_cookieJar);
        };
    }
}

void IArgumentTypeDetail::createHeaderJarType()
{
    static const auto types = makeTypes("IHeaderJar");
    if(types.contains(this->m_typeName)){
        this->m_createFun = [](IRequest& request)->void*{
            return &(request.impl().m_headerJar);
        };
    }
}

void IArgumentTypeDetail::createPartTypes()
{
    if(this->m_typeId != QMetaType::UnknownType){
        return;
    }
    static QList<decltype(&IArgumentTypeDetail::createRequestType)> funs = {
        &IArgumentTypeDetail::createMultiPartType,
        &IArgumentTypeDetail::createCookiePartType,
    };
    for(auto fun : funs){
        std::invoke(fun, this);
        if(m_createFun){
            return;
        }
    }
}

void IArgumentTypeDetail::createMultiPartType()
{
    static const auto types = makeTypes("IMultiPart");
    if(!types.contains(this->m_typeName)){
        return;
    }
    if(m_position != Position::Auto){
        qFatal("position should be empty");
    }
    auto self = *this;
    this->m_createFun = [=](IRequest& request) -> void*{
        if(request.mime() == IHttpMime::MULTIPART_FORM_DATA){
            const auto& value = request.multiPartJar().getMultiPart(self.m_name);
            if(&value == &IMultiPart::Empty){
                if(self.m_optional){
                    return self.m_optionalPtr;
                }
                request.setInvalid(IHttpInternalErrorInvalid("multitype not optional"));
                return nullptr;
            }
            return static_cast<void*>(const_cast<IMultiPart*>(&value));
        }
        request.setInvalid(IHttpInternalErrorInvalid("not multitype type"));
        return nullptr;
    };
}

void IArgumentTypeDetail::createCookiePartType()
{
    static const auto& types = makeTypes("ICookiePart");
    if(!types.contains(this->m_typeName)){
        return;
    }
    if(m_position != Position::Auto){
        qFatal("position should be empty");
    }
    auto self = *this;
    this->m_createFun = [=](IRequest& request) -> void*{
        if(request.impl().m_reqRaw.m_cookies.contains(self.m_name)){
            const auto& value = request.impl().m_reqRaw.m_cookies.value(self.m_name);
            return new ICookiePart(self.m_name, value);
        }
        if(self.m_optional){
            return m_optionalPtr;
        }
        request.setInvalid(IHttpInternalErrorInvalid("cookie not optional"));
        return nullptr;
    };
    this->m_destroyFun = [](void* ptr){
        if(ptr  && (ptr != &ICookiePart::Empty)){
            delete static_cast<ICookiePart*>(ptr);
        }
    };
}

void IArgumentTypeDetail::createDecorateTypes()
{
    QList<decltype(&IArgumentTypeDetail::createQueryType)> funs = {
        &IArgumentTypeDetail::createQueryType,
        &IArgumentTypeDetail::createHeaderType,
        &IArgumentTypeDetail::createCookieType,
        &IArgumentTypeDetail::createSessionType,
        &IArgumentTypeDetail::createPathType,
        &IArgumentTypeDetail::createBodyType,
        &IArgumentTypeDetail::createFormType,
        &IArgumentTypeDetail::createJsonType
    };

    for(auto fun : funs){
        std::invoke(fun, this);
        if(m_createFun){
            auto typeId = m_typeId;
            auto typeName = m_typeName;
            if(!this->m_destroyFun){
                this->m_destroyFun = [=](void* ptr){
                    detail::deletePtr(ptr, typeId, typeName);
                };
            }
            return;
        }
    }
}

void IArgumentTypeDetail::createQueryType()
{
    if(this->m_position != Position::Query){
        return;
    }
    if(!detail::isTypeConvertable(m_typeId, m_typeName)){
        qFatal("not convertable");
    }
    auto self = *this;
    this->m_createFun = [=](IRequest& req)->void*{
        if(req.impl().m_reqRaw.m_queries.contains(self.m_name.m_view)){
            auto data = req.impl().m_reqRaw.m_queries[self.m_name];
            return detail::convertPtr(data, self.m_typeId, self.m_typeName);
        }
        if(self.m_optional){
            return self.m_optionalPtr;
        }
        req.setInvalid(IHttpInternalErrorInvalid("not found arg"));
        return nullptr;
    };
}

void IArgumentTypeDetail::createHeaderType()
{
    if(this->m_position != Position::Header){
        return;
    }
    if(!detail::isTypeConvertable(m_typeId, m_typeName)){
        qFatal("error");
    }
    auto self = *this;
    this->m_createFun = [=](IRequest& request) ->void*{
        if(request.impl().m_reqRaw.m_headers.contains(self.m_name)){
            auto ptr = detail::convertPtr(request.impl().m_reqRaw.m_headers.value(self.m_name), self.m_typeId, self.m_typeName);
            if(!ptr){
                request.setInvalid(IHttpBadRequestInvalid("header field value not proper"));
            }
            return ptr;
        }
        if(self.m_optional){
            return self.m_optionalPtr;
        }
        request.setInvalid(IHttpInternalErrorInvalid("header field not resolved"));
        return nullptr;
    };
}

void IArgumentTypeDetail::createCookieType()
{
    if(this->m_position != Position::Cookie){
        return;
    }
    if(!detail::isTypeConvertable(m_typeId, m_typeName)){
        qFatal("not convertable");
    }
    auto self = *this;
    this->m_createFun = [=](IRequest& request) ->void*{
        if(detail::isMultipleType(self.m_typeId, self.m_typeName)){
            auto values = request.impl().m_reqRaw.m_cookies.values(self.m_name);
            if(!values.isEmpty()){
                auto ptr = detail::convertPtr(values, self.m_typeId, self.m_typeName);
                if(!ptr){
                    request.setInvalid(IHttpBadRequestInvalid("header field value not proper"));
                }
                return ptr;
            }
            if(self.m_optional){
                return self.m_optionalPtr;
            }
            request.setInvalid(IHttpInternalErrorInvalid("cookie missed"));
            return nullptr;
        }else{
            if(request.impl().m_reqRaw.m_cookies.contains(self.m_name)){
                auto value = request.impl().m_reqRaw.m_cookies.value(self.m_name);
                auto ptr = detail::convertPtr(value, self.m_typeId, self.m_typeName);
                if(!ptr){
                    request.setInvalid(IHttpBadRequestInvalid("header field value not proper"));
                }
                return ptr;
            }
            if(self.m_optional){
                return self.m_optionalPtr;
            }
            request.setInvalid(IHttpInternalErrorInvalid("cookie not found"));
            return nullptr;
        }
        return nullptr;
    };
}

void IArgumentTypeDetail::createSessionType()
{

}

void IArgumentTypeDetail::createPathType()
{
    if(this->m_position != Position::Path){
        return;
    }
    if(!detail::isTypeConvertable(m_typeId, m_typeName)){
        qFatal("not convertable");
    }
    if(this->m_optional){
        qFatal("path can`t be optional");
    }
    auto self = *this;
    this->m_createFun = [=](IRequest& req) -> void*{
        auto action = dynamic_cast<IHttpControllerAction*>(req.impl().m_action);
        auto index = action->m_path.m_actionNameMap[self.m_name];
        auto url = req.impl().m_reqRaw.m_url.split("/");
        auto value = url[index+1];      // 这里第一个数值是空
        auto ptr = detail::convertPtr(value, self.m_typeId, self.m_typeName);
        if(!ptr){
            req.setInvalid(IHttpBadRequestInvalid("path value can not be converted"));
        }
        return ptr;
    };
}

void IArgumentTypeDetail::createBodyType()
{
    if(this->m_position != Position::Body){
        return;
    }
    if(!detail::isTypeConvertable(m_typeId, m_typeName)){
        qFatal("not convertable");
    }
    static const auto& types = IConstantUtil::StringTypes;
    if(std::find(types.begin(), types.end(), m_typeName) == types.end()){
        qFatal("type must be string type, check it");       // TODO: 这个限制之后可以考虑放开。
    }
    auto self = *this;
    this->m_createFun = [=](IRequest& req)->void*{
        if(req.impl().m_reqRaw.m_contentLength == 0 && req.impl().m_reqRaw.m_isChunked==false){
            if(m_optional){
                return m_optionalPtr;
            }
            req.setInvalid(IHttpInternalErrorInvalid("request do not contain body"));
            return nullptr;
        }
        auto ptr = detail::convertPtr(req.impl().m_reqRaw.m_body, self.m_typeId, self.m_typeName);
        if(!ptr){
            req.setInvalid(IHttpBadRequestInvalid("body field can not be conveted"));
        }
        return ptr;
    };
}

void IArgumentTypeDetail::createFormType()
{
    if(this->m_position != Position::Form){
        return;
    }
    if(!detail::isTypeConvertable(m_typeId, m_typeName)){
        qFatal("not convertable");
    }
    auto self = *this;
    this->m_createFun = [=](IRequest& req)->void*{
        if(req.mime() != IHttpMime::APPLICATION_WWW_FORM_URLENCODED){
            req.setInvalid(IHttpInternalErrorInvalid("request should be form data"));
            return nullptr;
        }
        if(req.impl().m_reqRaw.m_forms.contains(self.m_name.m_view)){
            auto data = req.impl().m_reqRaw.m_forms[self.m_name];
            auto ptr = detail::convertPtr(data, self.m_typeId, self.m_typeName);
            if(!ptr){
                req.setInvalid(IHttpBadRequestInvalid("form field value not proper"));
            }
            return ptr;
        }
        if(self.m_optional){
            return m_optionalPtr;
        }
        req.setInvalid(IHttpInternalErrorInvalid("not found form value"));
        return nullptr;
    };
}

void IArgumentTypeDetail::createJsonType()
{
    static const auto types = makeTypes("IJson");
    if(!types.contains(m_typeName)){
        return;
    }
    if(m_position != Position::Auto && m_position != Position::Json){
        qFatal("IJson type postion must not exist or be $Json");
    }
    if(m_optional){
        qFatal("IJson can not be optional currently");
    }

    auto self = *this;
    auto pointer = createJsonPointer(m_name);
    this->m_createFun = [=](IRequest& request)->void*{
        if(request.mime() != IHttpMime::APPLICATION_JSON
                && request.mime() != IHttpMime::APPLICATION_JSON_UTF8){
            request.setInvalid(IHttpInternalErrorInvalid("request do not contain json payload"));
            return nullptr;
        }
        const auto& json = request.impl().m_reqRaw.m_json;
        if(self.m_position == Position::Auto){
            return const_cast<IJson*>(&json);
        }
        if(json.contains(pointer)){
            return new IJson(json[pointer]);
        }
        request.setInvalid(IHttpInternalErrorInvalid("not found json body"));
        return nullptr;
    };
    this->m_destroyFun = [=](void* ptr){
        if(self.m_position == Position::Json){
            delete static_cast<IJson*>(ptr);
        }
    };
}

void IArgumentTypeDetail::createBeanTypes()
{
    if(!IBeanTypeManage::instance()->isBeanIdExist(m_typeId)){
        return;
    }
    auto self = *this;
    this->m_createFun = [=](IRequest& req)->void*{
        if(req.mime() != IHttpMime::APPLICATION_JSON && req.mime() != IHttpMime::APPLICATION_JSON_UTF8){
            req.setInvalid(IHttpBadRequestInvalid("bean only for json payload currently"));
            return nullptr;
        }
        auto ptr = QMetaType::create(self.m_typeId);
        if(!IBeanTypeManage::instance()->getBeanFromJson(self.m_typeId)(ptr, req.bodyJson())){
            req.setInvalid(IHttpInternalErrorInvalid("json can not be converted to Bean"));
        }
        return ptr;
    };
    this->m_destroyFun = [=](void* ptr){
        if(ptr){
            QMetaType::destroy(self.m_typeId, ptr);
        }
    };
}

QVector<IString> IArgumentTypeDetail::makeTypes(const std::string &name)
{
    return QVector<IString> {
        name, name + "&",
        std::string($PackageWebCoreName) + "::" + name,
        std::string($PackageWebCoreName) + "::" + name + "&"
    };
}

IJson::json_pointer IArgumentTypeDetail::createJsonPointer(const IString & data)
{
    QString path = data.toQString().replace("$", "/");
    if(!path.startsWith("/")){
        path = "/"+path;
    }
    IJson::json_pointer pointer(path.toStdString());
    return pointer;
}

namespace ISpawnUtil {
    template<>
    IArgumentType construct(int paramTypeId, QByteArray paramTypeName, QByteArray paramName)
    {
        return IArgumentTypeDetail(paramTypeId, std::move(paramTypeName), std::move(paramName));
    }
}

$PackageWebCoreEnd
