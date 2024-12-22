#include "IArgumentTypeDetail.h"
#include "core/util/ISpawnUtil.h"
#include "core/util/IConstantUtil.h"
#include "core/bean/IBeanTypeManage.h"
#include "http/controller/IHttpControllerAbort.h"
#include "http/IHttpManage.h"
#include "http/invalid/IHttpInternalErrorInvalid.h"
#include "http/invalid/IHttpBadRequestInvalid.h"
#include "http/net/IRequest.h"
#include "http/net/IResponse.h"
#include "http/net/ICookieJar.h"
#include "http/net/ISessionJar.h"
#include "http/net/IMultiPartJar.h"
#include "http/net/IHeaderJar.h"
#include "http/net/impl/IRequestImpl.h"

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
            "IString", "std::string", "IStringView", "QList<IString>", "QStringList"
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
    }

    // TODO: 这里考虑一下支持转换到 QStringList 之类的内容
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

    static QList<decltype(&IArgumentTypeDetail::createBasicType)> funs = {
        &IArgumentTypeDetail::createBasicType,
        &IArgumentTypeDetail::createPartTypes,
        &IArgumentTypeDetail::createDecorateTypes
    };
    for(auto fun : funs){
        if(std::mem_fn(fun)(this)){
            return;
        }
    }
}

void IArgumentTypeDetail::resolveName()
{
    static const QVector<IString> PREFIXES = {
        "auto", "path", "query", "header", "cookie", "session", "body", "form", "json"
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
        if(arg.startWith("optional")){
            if(m_optional == true){
                qFatal("two more optional");
            }
            m_optional = true;
            auto spliter = arg.find("$$");
            if(spliter != std::string_view::npos){
                m_optionalString = arg.substr(spliter+2);
            }
        }
    }
}

bool IArgumentTypeDetail::createBasicType()
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
        return false;
    }

    for(auto fun : funs){
        std::mem_fn(fun)(this);
        if(this->m_createFun){
            if(m_optional){
                qFatal("optional can not be exist here");
            }
            if(m_position != Position::Auto){
                qFatal("position should be empty");
            }
            return true;
        }
    }
    return false;
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

bool IArgumentTypeDetail::createPartTypes()
{
    if(this->m_typeId != QMetaType::UnknownType){
        return false;
    }
    static QList<decltype(&IArgumentTypeDetail::createRequestType)> funs = {
        &IArgumentTypeDetail::createMultiPartType,
        &IArgumentTypeDetail::createCookiePartType,
    };
    for(auto fun : funs){
        std::mem_fn(fun)(this);
        if(this->m_createFun){
            return true;
        }
    }
    return false;
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
        if(request.contentType().startWith(IHttpMimeUtil::toString(IHttpMime::MULTIPART_FORM_DATA))){ // TODO: force little case
            const auto& value = request.multiPartJar().getMultiPart(self.m_name);
            if(!self.m_optional && (&value == &IMultiPart::Empty)){
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
    if(m_optional && !m_optionalString.isEmpty()){
        qFatal("in cookiepart, no optional variable needed"); // optional 不需要给定参数值,默认是 Empty
    }

    auto self = *this;
    this->m_createFun = [=](IRequest& request) -> void*{
        if(request.impl().m_reqRaw.m_cookies.contains(self.m_name)){
            const auto& value = request.impl().m_reqRaw.m_cookies.value(self.m_name);
            return new ICookiePart(self.m_name, value.m_stringView);
        }
        if(self.m_optional){
            return static_cast<void*>(const_cast<ICookiePart*>(&ICookiePart::Empty));
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

bool IArgumentTypeDetail::createDecorateTypes()
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
        std::mem_fn(fun)(this);
        if(this->m_createFun){
            auto typeId = m_typeId;
            auto typeName = m_typeName;
            this->m_destroyFun = [=](void* ptr){
                detail::deletePtr(ptr, typeId, typeName);
            };
            return true;
        }
    }
    return false;
}

void IArgumentTypeDetail::createQueryType()
{

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
            return detail::convertPtr(self.m_optionalString, self.m_typeId, self.m_typeName);
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
                return detail::convertPtr(values, self.m_typeId, self.m_typeName);
            }
            if(self.m_optional){
                return detail::convertPtr(QList<IString>{}, self.m_typeId, self.m_typeName);
            }
            request.setInvalid(IHttpInternalErrorInvalid("cookie missed"));
            return nullptr;
        }else{
            if(request.impl().m_reqRaw.m_cookies.contains(self.m_name)){
                auto value = request.impl().m_reqRaw.m_cookies.value(self.m_name);
                return detail::convertPtr(value, self.m_typeId, self.m_typeName);
            }
            if(self.m_optional){
                return detail::convertPtr(self.m_optionalString, self.m_typeId, self.m_typeName);
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
        if(!req.impl().m_reqRaw.m_body.isEmpty()){
            return detail::convertPtr(req.impl().m_reqRaw.m_body, self.m_typeId, self.m_typeName);
        }
        return detail::convertPtr(self.m_optionalString, self.m_typeId, self.m_typeName);
    };
}

void IArgumentTypeDetail::createFormType()
{

}

void IArgumentTypeDetail::createJsonType()
{

}

bool IArgumentTypeDetail::createBeanTypes()
{
    return false;
}

bool IArgumentTypeDetail::createDataTypes()
{
    return false;
}

QVector<IString> IArgumentTypeDetail::makeTypes(const std::string &name)
{
    return QVector<IString> {
        name, name + "&",
        std::string($PackageWebCoreName) + "::" + name,
        std::string($PackageWebCoreName) + "::" + name + "&"
    };
}

namespace ISpawnUtil {
    template<>
    IArgumentType construct(int paramTypeId, QByteArray paramTypeName, QByteArray paramName)
    {
        return IArgumentTypeDetail(paramTypeId, std::move(paramTypeName), std::move(paramName));
    }
}

$PackageWebCoreEnd
