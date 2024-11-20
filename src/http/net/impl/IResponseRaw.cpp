#include "IResponseRaw.h"

$PackageWebCoreBegin

void IResponseRaw::setMime(IHttpMime mime)
{
    this->mime = IHttpMimeUtil::toString(mime);
}

void IResponseRaw::setMime(const QString &mime)
{
    this->mime = mime;
}

void IResponseRaw::setContent(QString &&value)
{
    content.setContent(std::move(value));
}

void IResponseRaw::setContent(const QString &value)
{
    content.setContent(value);
}

void IResponseRaw::setContent(QByteArray &&value)
{
    content.setContent(std::move(value));
}

void IResponseRaw::setContent(const QByteArray &value)
{
    content.setContent(value);
}

void IResponseRaw::setContent(const char *value)
{
    content.setContent(QByteArray(value));
}

void IResponseRaw::setContent(const QFileInfo &value)
{
    content.setFileContent(value.absoluteFilePath());
}

void IResponseRaw::setContent(IHttpInvalidWare ware)
{
    content.setContent(std::move(ware));
}

$PackageWebCoreEnd
