#include "IByteArrayResponse.h"

$PackageWebCoreBegin

IByteArrayResponse::IByteArrayResponse()
{
    m_raw->setMime(IHttpMime::APPLICATION_OCTET_STREAM);
}

IByteArrayResponse::IByteArrayResponse(QString val) : IByteArrayResponse(val.toUtf8())
{
}

IByteArrayResponse::IByteArrayResponse(const char *array)
    : IByteArrayResponse(QByteArray::fromRawData(array, static_cast<std::size_t>(strlen(array))))
{
}

IByteArrayResponse::IByteArrayResponse(QByteArray &array)
{
    m_raw->setContent(array);
    m_raw->setMime(IHttpMime::APPLICATION_OCTET_STREAM);
}

IByteArrayResponse::IByteArrayResponse(QByteArray &&array)
{
    m_raw->setContent(std::forward<QByteArray>(array));
    m_raw->setMime(IHttpMime::APPLICATION_OCTET_STREAM);
}

QString IByteArrayResponse::getPrefixMatcher()
{
    return "$bytes:";
}

IByteArrayResponse operator"" _bytes(const char* str, size_t size){
    return QByteArray::fromRawData(str, static_cast<int>(size));
}

$PackageWebCoreEnd
