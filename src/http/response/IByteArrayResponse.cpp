#include "IByteArrayResponse.h"
#include "http/response/content/IResponseContent.h"

$PackageWebCoreBegin

IByteArrayResponse::IByteArrayResponse()
{
    m_raw->setMime(IHttpMime::APPLICATION_OCTET_STREAM);
}

IByteArrayResponse::IByteArrayResponse(const char *data)
    : IByteArrayResponse(QByteArray(data))
{
}

IByteArrayResponse::IByteArrayResponse(QByteArray &&array)
{
    m_raw->setMime(IHttpMime::APPLICATION_OCTET_STREAM);
    m_raw->setContent(new IResponseContent(std::move(array)));
}

IByteArrayResponse::IByteArrayResponse(const QByteArray &array)
{
    m_raw->setMime(IHttpMime::APPLICATION_OCTET_STREAM);
    m_raw->setContent(new IResponseContent(array));
}

IByteArrayResponse::IByteArrayResponse(const QString &data)
{
    m_raw->setMime(IHttpMime::APPLICATION_OCTET_STREAM);
    m_raw->setContent(new IResponseContent(data.toUtf8()));
}

IByteArrayResponse::IByteArrayResponse(std::string &&data)
{
    m_raw->setMime(IHttpMime::APPLICATION_OCTET_STREAM);
    m_raw->setContent(new IResponseContent(std::move(data)));
}

IByteArrayResponse::IByteArrayResponse(const std::string & data)
{
    m_raw->setMime(IHttpMime::APPLICATION_OCTET_STREAM);
    m_raw->setContent(new IResponseContent(data));
}

std::string IByteArrayResponse::prefixMatcher()
{
    return "$bytes:";
}

IByteArrayResponse operator"" _bytes(const char* str, size_t size){
    return QByteArray::fromRawData(str, static_cast<int>(size));
}

$PackageWebCoreEnd
