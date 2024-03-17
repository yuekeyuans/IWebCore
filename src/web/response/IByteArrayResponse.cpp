#include "IByteArrayResponse.h"

$PackageWebCoreBegin

IByteArrayResponse::IByteArrayResponse()
{
    raw->setMime(IHttpMime::APPLICATION_OCTET_STREAM);
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
    raw->setContent(array);
    raw->setMime(IHttpMime::APPLICATION_OCTET_STREAM);
}

IByteArrayResponse::IByteArrayResponse(QByteArray &&array)
{
    raw->setContent(std::forward<QByteArray>(array));
    raw->setMime(IHttpMime::APPLICATION_OCTET_STREAM);
}

QString IByteArrayResponse::getPrefixMatcher()
{
    return "$bytes:";
}

QSharedPointer<IResponseWare> IByteArrayResponse::createByteArrayInstance()
{
    return QSharedPointer<IByteArrayResponse>::create();
}

IByteArrayResponse operator"" _bytes(const char* str, size_t size){
    return QByteArray::fromRawData(str, static_cast<int>(size));
}

$PackageWebCoreEnd
