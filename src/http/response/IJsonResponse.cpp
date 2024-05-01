#include "IJsonResponse.h"
#include "IResponseManage.h"
#include "http/net/impl/IResponseRaw.h"

$PackageWebCoreBegin

IJsonResponse::IJsonResponse() : IResponseInterface()
{
    m_raw->setMime(IHttpMime::APPLICATION_JSON_UTF8); // this must be initialized, the only return type;
}

IJsonResponse::IJsonResponse(const QString& value) : IResponseInterface()
{
    m_raw->setMime(IHttpMime::APPLICATION_JSON_UTF8);
    m_raw->setContent(value);
}

IJsonResponse::IJsonResponse(const QJsonValue &value) : IResponseInterface()
{
    m_raw->setMime(IHttpMime::APPLICATION_JSON_UTF8);
    m_raw->setContent(IJsonUtil::toString(value));
}

IJsonResponse::IJsonResponse(const QJsonArray &array) : IResponseInterface()
{
    m_raw->setMime(IHttpMime::APPLICATION_JSON_UTF8);
    m_raw->setContent(IJsonUtil::toString(array));
}

IJsonResponse::IJsonResponse(const QJsonObject &object) : IResponseInterface()
{
    m_raw->setMime(IHttpMime::APPLICATION_JSON_UTF8);
    m_raw->setContent(IJsonUtil::toString(object));
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
