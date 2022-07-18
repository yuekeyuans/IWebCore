#include "IResponseWareRaw.h"

$PackageWebCoreBegin

void IResponseWareRaw::setMime(IHttpMime mime){
    this->mimeString = IHttpMimeHelper::toString(mime);
}

void IResponseWareRaw::setMime(const QString &mime){
    this->mimeString = mime;
}

void IResponseWareRaw::setContent(QString &&value)
{
    content.type = IResponseContent::String;
    std::swap(content.contentString, value);
}

void IResponseWareRaw::setContent(const QString &value)
{
    content.type = IResponseContent::String;
    content.contentString = value;
}

void IResponseWareRaw::setContent(QByteArray &&value)
{
    content.type = IResponseContent::Bytes;
    std::swap(content.contentBytes, value);
}

void IResponseWareRaw::setContent(const QByteArray &value)
{
    content.type = IResponseContent::Bytes;
    content.contentBytes = value;
}

void IResponseWareRaw::setContent(const char *value)
{
    content.type = IResponseContent::Bytes;
    content.contentBytes = QByteArray(value);
}

void IResponseWareRaw::setContent(const QFileInfo &value)
{
    content.type = IResponseContent::File;
    content.contentFilePath = value.absoluteFilePath();
}

void IResponseWareRaw::setContent(const QFile &file)
{
    content.type = IResponseContent::File;
    content.contentFilePath = QFileInfo(file).absoluteFilePath();
}

void IResponseWareRaw::setFileContent(const QString &filePath)
{
    content.type = IResponseContent::File;
    content.contentFilePath = filePath;
}

$PackageWebCoreEnd
