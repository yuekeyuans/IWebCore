#include "IJsonResponse.h"
#include "IResponseManage.h"
#include "http/detail/IResponseRaw.h"

$PackageWebCoreBegin

IJsonResponse::IJsonResponse()
{
    m_raw->setMime(IHttpMime::APPLICATION_JSON_UTF8); // this must be initialized, the only return type;
}

IJsonResponse::IJsonResponse(IJson && json)
{
    m_raw->setMime(IHttpMime::APPLICATION_JSON_UTF8);
    m_raw->setContent(new IResponseContent(json.dump()));
}

IJsonResponse::IJsonResponse(const IJson &json)
{
    m_raw->setMime(IHttpMime::APPLICATION_JSON_UTF8);
    m_raw->setContent(new IResponseContent(json.dump()));
}

IJsonResponse::IJsonResponse(const char * value)
{
    m_raw->setMime(IHttpMime::APPLICATION_JSON_UTF8);
    m_raw->setContent(new IResponseContent(std::string(value)));
}

IJsonResponse::IJsonResponse(std::string&& value)
{
    m_raw->setMime(IHttpMime::APPLICATION_JSON_UTF8);
    m_raw->setContent(new IResponseContent(std::move(value)));
}

IJsonResponse::IJsonResponse(const QString& value) : IResponseInterface()
{
    m_raw->setMime(IHttpMime::APPLICATION_JSON_UTF8);
    m_raw->setContent(new IResponseContent(value.toStdString()));
}

std::string IJsonResponse::prefixMatcher()
{
    return "$json:";
}

IJsonResponse operator"" _json(const char *str, size_t size)
{
    auto data = std::string(str, static_cast<int>(size));
    return IJsonResponse(std::move(data));
}

$PackageWebCoreEnd
