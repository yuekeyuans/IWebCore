#include "IJsonResponse.h"
#include "IResponseManage.h"
#include "IResponseWareRaw.h"

$PackageWebCoreBegin

const QString IJsonResponse::prefix {"$json:"};

IJsonResponse::IJsonResponse() : IResponseInterface()
{
    raw->mime = IHttpMime::APPLICATION_JSON_UTF8; // this must be initialized, the only return type;
}

IJsonResponse::IJsonResponse(const QString& value) : IResponseInterface()
{
    raw->mime = IHttpMime::APPLICATION_JSON_UTF8;
    raw->content = value.toUtf8();
}

IJsonResponse::IJsonResponse(const QJsonValue &value) : IResponseInterface()
{
    raw->mime = IHttpMime::APPLICATION_JSON_UTF8;
    raw->content = IJsonUtil::toString(value).toUtf8();
}

IJsonResponse::IJsonResponse(const QJsonArray &array) : IResponseInterface()
{
    raw->mime = IHttpMime::APPLICATION_JSON_UTF8;
    raw->content = IJsonUtil::toString(array).toUtf8();
}

IJsonResponse::IJsonResponse(const QJsonObject &object) : IResponseInterface()
{
    raw->mime = IHttpMime::APPLICATION_JSON_UTF8;
    raw->content = IJsonUtil::toString(object).toUtf8();
}

IJsonResponse::IJsonResponse(IRedirectResponse &&redirectResponse)
{
    redirectTo(std::forward<IRedirectResponse&&>(redirectResponse));
}

void IJsonResponse::setInstanceArg(QString &&value)
{
    raw->content = value.midRef(prefix.length()).toUtf8();
}

void IJsonResponse::setInstanceArg(void *arg, const QString &type)
{
    if(type == "QJsonObject"){
        auto value = *static_cast<QJsonObject*>(arg);
        raw->content = IJsonUtil::toString(value).toUtf8();
    }else if(type == "QJsonArray"){
        auto value = *static_cast<QJsonArray*>(arg);
        raw->content = IJsonUtil::toString(value).toUtf8();
    }else if(type == "QJsonValue"){
        auto value = *static_cast<QJsonValue*>(arg);
        raw->content = IJsonUtil::toString(value).toUtf8();
    }
}

bool IJsonResponse::canConvertFromString()
{
    return true;
}

bool IJsonResponse::matchConvertString(const QString &value)
{
    return value.startsWith(prefix);
}

QSharedPointer<IJsonResponse> IJsonResponse::createJsonInstance()
{
    return QSharedPointer<IJsonResponse>(new IJsonResponse);
}

QSharedPointer<IResponseWare> IJsonResponse::createInstance()
{
    return QSharedPointer<IResponseWare>(new IJsonResponse);
}

IJsonResponse operator"" _json(const char *str, size_t size)
{
    auto data = QString::fromLocal8Bit(str, static_cast<int>(size));
    return IJsonResponse(std::move(data));
}

$PackageWebCoreEnd
