#include "IJsonResponse.h"
#include "IResponseManage.h"
#include "http/net/impl/IResponseRaw.h"
#include "http/response/content/IIJsonResponseContent.h"

$PackageWebCoreBegin

IJsonResponse::IJsonResponse() : IResponseInterface()
{
    m_raw->setMime(IHttpMime::APPLICATION_JSON_UTF8); // this must be initialized, the only return type;
}

IJsonResponse::IJsonResponse(IJson && json)
{
    m_raw->setContent(std::move(json));
    m_raw->setMime(IHttpMime::APPLICATION_JSON_UTF8);
}

IJsonResponse::IJsonResponse(const IJson &json)
{
    m_raw->setMime(IHttpMime::APPLICATION_JSON_UTF8);
    m_raw->setContent(json);
}

IJsonResponse::IJsonResponse(const char * value)
{
    m_raw->setMime(IHttpMime::APPLICATION_JSON_UTF8);
    m_raw->setContent(new IIJsonResponseContent(std::string(value)));
}

IJsonResponse::IJsonResponse(std::string&& value)
{
    m_raw->setMime(IHttpMime::APPLICATION_JSON_UTF8);
    m_raw->setContent(new IIJsonResponseContent(std::move(value)));
}

IJsonResponse::IJsonResponse(const QString& value) : IResponseInterface()
{
    m_raw->setMime(IHttpMime::APPLICATION_JSON_UTF8);
    m_raw->setContent(new IIJsonResponseContent(value.toStdString()));
}

//IJsonResponse::IJsonResponse(const QJsonValue &value) : IResponseInterface()
//{
//    m_raw->setMime(IHttpMime::APPLICATION_JSON_UTF8);
//    if(value.isArray()){
//        m_raw->setContent(QJsonDocument(value.toArray()).toJson());
//    }else if(value.isObject()){
//        m_raw->setContent(QJsonDocument(value.toObject()).toJson());
//    }else if(value.isString()){
//        m_raw->setContent(value.toString());
//    }else if(value.isDouble()){
//        m_raw->setContent(QString::number(value.toDouble()));
//    }
//}

//IJsonResponse::IJsonResponse(const QJsonArray &array) : IResponseInterface()
//{
//    m_raw->setMime(IHttpMime::APPLICATION_JSON_UTF8);
//    m_raw->setContent(QJsonDocument(array).toJson());
//}

//IJsonResponse::IJsonResponse(const QJsonObject &object) : IResponseInterface()
//{
//    m_raw->setMime(IHttpMime::APPLICATION_JSON_UTF8);
//    m_raw->setContent(QJsonDocument(object).toJson());
//}

QString IJsonResponse::prefixMatcher()
{
    return "$json:";
}

IJsonResponse operator"" _json(const char *str, size_t size)
{
    auto data = std::string(str, static_cast<int>(size));
    return IJsonResponse(std::move(data));
}

$PackageWebCoreEnd
