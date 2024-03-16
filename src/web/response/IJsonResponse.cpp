#include "IJsonResponse.h"
#include "IResponseManage.h"
#include "IResponseWareRaw.h"

$PackageWebCoreBegin

const QString IJsonResponse::prefix {"$json:"};

IJsonResponse::IJsonResponse() : IResponseInterface()
{
    raw->setMime(IHttpMime::APPLICATION_JSON_UTF8); // this must be initialized, the only return type;
}

IJsonResponse::IJsonResponse(const QString& value) : IResponseInterface()
{
    raw->setMime(IHttpMime::APPLICATION_JSON_UTF8);
    raw->setContent(value);
}

IJsonResponse::IJsonResponse(const QJsonValue &value) : IResponseInterface()
{
    raw->setMime(IHttpMime::APPLICATION_JSON_UTF8);
    raw->setContent(IJsonUtil::toString(value));
}

IJsonResponse::IJsonResponse(const QJsonArray &array) : IResponseInterface()
{
    raw->setMime(IHttpMime::APPLICATION_JSON_UTF8);
    raw->setContent(IJsonUtil::toString(array));
}

IJsonResponse::IJsonResponse(const QJsonObject &object) : IResponseInterface()
{
    raw->setMime(IHttpMime::APPLICATION_JSON_UTF8);
    raw->setContent(IJsonUtil::toString(object));
}

void IJsonResponse::setInstanceArg(QString &&value)
{
    raw->setContent(value.mid(prefix.length()));
}

void IJsonResponse::setInstanceArg(void *arg, const QString &type)
{
    if(type == "QJsonObject"){
        auto value = *static_cast<QJsonObject*>(arg);
        raw->setContent(IJsonUtil::toString(value));
    }else if(type == "QJsonArray"){
        auto value = *static_cast<QJsonArray*>(arg);
        raw->setContent(IJsonUtil::toString(value));
    }else if(type == "QJsonValue"){
        auto value = *static_cast<QJsonValue*>(arg);
        raw->setContent(IJsonUtil::toString(value));
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
    return QSharedPointer<IJsonResponse>::create();
}

QSharedPointer<IResponseWare> IJsonResponse::createInstance()
{
    return QSharedPointer<IJsonResponse>::create();
}

IJsonResponse operator"" _json(const char *str, size_t size)
{
    auto data = QString::fromLocal8Bit(str, static_cast<int>(size));
    return IJsonResponse(std::move(data));
}

$PackageWebCoreEnd
