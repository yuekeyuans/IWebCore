#include "IArgumentTypeDetail.h"
#include "core/util/ISpawnUtil.h"
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
    static bool isTypeConvertable(QMetaType::Type typeId, const IString& typeName)
    {
        static QList<QMetaType::Type> types = {
            QMetaType::Bool, QMetaType::SChar, QMetaType::UChar,
            QMetaType::UShort, QMetaType::Short, QMetaType::Int, QMetaType::UInt,
            QMetaType::ULong, QMetaType::Long, QMetaType::ULongLong, QMetaType::LongLong,
            QMetaType::Float, QMetaType::Double, QMetaType::QString, QMetaType::QByteArray,
        };
        static QList<IString> typeNames = {
            "IString", "std::string"
        };
        return types.contains(typeId) || typeNames.contains(typeName);
    }

    static void* convertPtr(const IString& data, QMetaType::Type typeId, const IString& typeName, bool& ok)
    {
        switch (typeId) {
        case QMetaType::Bool:
            return data.valuePtr<bool>(ok);
        case QMetaType::SChar:
            return data.valuePtr<signed char>(ok);
        case QMetaType::UChar:
            return data.valuePtr<unsigned char>(ok);
        case QMetaType::Short:
            return data.valuePtr<signed short>(ok);
        case QMetaType::UShort:
            return data.valuePtr<unsigned short>(ok);
        case QMetaType::Int:
            return data.valuePtr<signed int>(ok);
        case QMetaType::UInt:
            return data.valuePtr<unsigned int>(ok);
        case QMetaType::Long:
            return data.valuePtr<signed long>(ok);
        case QMetaType::ULong:
            return data.valuePtr<unsigned long>(ok);
        case QMetaType::LongLong:
            return data.valuePtr<signed long long>(ok);
        case QMetaType::ULongLong:
            return data.valuePtr<unsigned long long>(ok);
        case QMetaType::Float:
            return data.valuePtr<float>(ok);
        case QMetaType::Double:
            return data.valuePtr<double>(ok);
        case QMetaType::QString:
            return data.valuePtr<QString>(ok);
        case QMetaType::QByteArray:
            return data.valuePtr<QByteArray>(ok);
        default:
            break;
        }
        if(typeName == "IString"){
            return data.valuePtr<IString>(ok);
        }else if(typeName == "std::string"){
            return data.valuePtr<std::string>(ok);
        }
        qFatal("not supported type");
        return nullptr;
    }

    static void deletePtr(void* ptr, QMetaType::Type typeId, const IString& typeName)
    {
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
        default:
            break;
        }
        if(typeName == "IString"){
            return delete static_cast<IString*>(ptr);
        }else if(typeName == "std::string"){
            return delete static_cast<std::string*>(ptr);
        }else{
            qFatal("error"); // TODO:
        }

    }
}

IArgumentTypeDetail::IArgumentTypeDetail(int typeId, QByteArray paramTypeName, QByteArray nameRaw)
    : IArgumentType()
{
    m_typeId = QMetaType::Type(typeId);
    m_typeName = std::move(paramTypeName);
    m_nameRaw = std::move(nameRaw);

    if(m_nameRaw.isEmpty()){
        qFatal("Name should not be empty");
    }

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
        "auto", "path", "query", "header", "cookie", "session", "form", "json"
    };
    IStringViewList args = m_nameRaw.split("_$");
    m_name = args.first();
    args.pop_front();

    for(IStringView arg : args){
        if(arg.startWith("Optional")){
            if(m_optional == true){
                qFatal("two more optional");
            }
            m_optional = true;
            continue;
        }

        auto index = PREFIXES.indexOf(arg);
        if(index > 0){
            if(m_position > 0){
                qFatal("two more restrict");
            }
            m_position = Position(index);
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

    bool m_optional = this->m_optional;         // weired!!!
    IString m_name = this->m_name;
    this->m_createFun = [m_optional, m_name](IRequest& request) -> void*{
        if(!request.bodyContentType().startWith(IHttpMimeUtil::toString(IHttpMime::MULTIPART_FORM_DATA))){ // TODO: force little case
            request.setInvalid(IHttpInternalErrorInvalid("not multitype type"));
            return nullptr;
        }else{
            const auto& value = request.multiPartJar().getMultiPart(m_name);
            if(!m_optional && (&value == &IMultiPart::Empty)){
                request.setInvalid(IHttpInternalErrorInvalid("multitype not optional"));
                return nullptr;
            }
            return static_cast<void*>(const_cast<IMultiPart*>(&value));
        }
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

    bool m_optional = this->m_optional;         // weired!!!
    IString m_name = this->m_name;
    this->m_createFun = [m_optional, m_name](IRequest& request) -> void*{
        if(request.impl().m_reqRaw.m_requestCookieParameters.contains(m_name)){
            auto value = request.impl().m_reqRaw.m_requestCookieParameters.value(m_name);
            return new ICookiePart(m_name, value);
        }
        if(m_optional){
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

    bool m_optional = this->m_optional;
    IString name = this->m_name;
    QMetaType::Type m_typeId = this->m_typeId;
    IString m_typeName = this->m_typeName;
    this->m_createFun = [=](IRequest& request)->void*{
        if(request.impl().m_reqRaw.m_requestHeaders.contain(name)){
            bool ok;
            auto value = request.impl().m_reqRaw.m_requestHeaders.value(name);
            auto ptr = detail::convertPtr(value, m_typeId, m_typeName, ok);
            if(!ok){
                request.setInvalid(IHttpBadRequestInvalid("value not proper"));
            }
            return ptr;
        }
        if(m_optional){
            // TODO: 这里需要重新设计，关于 optional 应该返回什么东西。
        }
        request.setInvalid(IHttpInternalErrorInvalid("header not resolved"));
        return nullptr;
    };
}

void IArgumentTypeDetail::createCookieType()
{

}

void IArgumentTypeDetail::createSessionType()
{

}

void IArgumentTypeDetail::createPathType()
{

}

void IArgumentTypeDetail::createBodyType()
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
    QVector<IString> names;
    names.append(name);
    names.append((name + "&"));
    names.append((std::string($PackageWebCoreName) + "::" + name));
    names.append((std::string($PackageWebCoreName) + "::" + name + "&"));

    return names;
}

namespace ISpawnUtil {
    template<>
    IArgumentType construct(int paramTypeId, QByteArray paramTypeName, QByteArray paramName)
    {
        return IArgumentTypeDetail(paramTypeId, std::move(paramTypeName), std::move(paramName));
    }
}

$PackageWebCoreEnd
