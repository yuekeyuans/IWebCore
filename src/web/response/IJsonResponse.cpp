#include "IJsonResponse.h"
#include "IResponseManage.h"
#include "IResponseWareRaw.h"

$PackageWebCoreBegin

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

QString IJsonResponse::getPrefixMatcher()
{
    return "$json:";
}

IJsonResponse operator"" _json(const char *str, size_t size)
{
    auto data = QString::fromLocal8Bit(str, static_cast<int>(size));
    return IJsonResponse(std::move(data));
}

$PackageWebCoreEnd
