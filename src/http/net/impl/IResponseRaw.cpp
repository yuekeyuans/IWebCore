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
    content.type = IResponseContent::Type::String;
    std::swap(content.contentString, value);
}

void IResponseRaw::setContent(const QString &value)
{
    content.type = IResponseContent::Type::String;
    content.contentString = value;
}

void IResponseRaw::setContent(QByteArray &&value)
{
    content.type = IResponseContent::Type::Bytes;
    std::swap(content.contentBytes, value);
}

void IResponseRaw::setContent(const QByteArray &value)
{
    content.type = IResponseContent::Type::Bytes;
    content.contentBytes = value;
}

void IResponseRaw::setContent(const char *value)
{
    content.type = IResponseContent::Type::Bytes;
    content.contentBytes = QByteArray(value);
}

void IResponseRaw::setContent(const QFileInfo &value)
{
    content.type = IResponseContent::Type::File;
    content.contentString = value.absoluteFilePath();
}

void IResponseRaw::setContent(const QFile &file)
{
    content.type = IResponseContent::Type::File;
    content.contentString = QFileInfo(file).absoluteFilePath();
}

void IResponseRaw::setContent(IHttpInvalidUnit ware)
{
    content.setContent(std::forward<IHttpInvalidUnit>(ware));
}

void IResponseRaw::setFileContent(const QString &filePath)
{
    content.type = IResponseContent::Type::File;
    content.contentString = filePath;
}

bool IResponseRaw::valid()
{
    return content.type == IResponseContent::Type::Invalid;
}

$PackageWebCoreEnd
