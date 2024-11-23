#include "IByteArrayResponse.h"

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
    m_raw->setContent(std::move(array));
}

IByteArrayResponse::IByteArrayResponse(const QByteArray &array)
{
    m_raw->setMime(IHttpMime::APPLICATION_OCTET_STREAM);
    m_raw->setContent(array);
}

IByteArrayResponse::IByteArrayResponse(const QString &data)
    : IByteArrayResponse(data.toUtf8())
{
}

QString IByteArrayResponse::prefixMatcher()
{
    return "$bytes:";
}

IByteArrayResponse operator"" _bytes(const char* str, size_t size){
    return QByteArray::fromRawData(str, static_cast<int>(size));
}

$PackageWebCoreEnd
