#include "IResponseWareRaw.h"

void IWebCore::IResponseWareRaw::setContent(const QString &content)
{
    contentType = ContentType::String;
    this->contentString = content;
}

void IWebCore::IResponseWareRaw::setContent(const QByteArray &content)
{
    contentType = ContentType::Bytes;
    this->contentBytes = content;
}

void IWebCore::IResponseWareRaw::setContent(const char *content)
{
    contentType = ContentType::Bytes;
    contentBytes = QByteArray(content);
}

void IWebCore::IResponseWareRaw::setContent(const QFileInfo &content)
{
    contentType = ContentType::File;
    contentFile = content.absoluteFilePath();
}

void IWebCore::IResponseWareRaw::setContent(const QFile &file)
{
    contentType = ContentType::File;
    contentFile = QFileInfo(file).absoluteFilePath();
}

void IWebCore::IResponseWareRaw::setFileContent(const QString &filePath)
{
    contentType = ContentType::File;
    contentFile = filePath;
}
