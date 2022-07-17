#include "IResponseWareRaw.h"

void IWebCore::IResponseWareRaw::setContent(QString &&value)
{
    content.type = IResponseContent::String;
    std::swap(content.contentString, value);
}

void IWebCore::IResponseWareRaw::setContent(const QString &value)
{
    content.type = IResponseContent::String;
    content.contentString = value;
}

void IWebCore::IResponseWareRaw::setContent(QByteArray &&value)
{
    content.type = IResponseContent::Bytes;
    std::swap(content.contentBytes, value);
}

void IWebCore::IResponseWareRaw::setContent(const QByteArray &value)
{
    content.type = IResponseContent::Bytes;
    content.contentBytes = value;
}

void IWebCore::IResponseWareRaw::setContent(const char *value)
{
    content.type = IResponseContent::Bytes;
    content.contentBytes = QByteArray(value);
}

void IWebCore::IResponseWareRaw::setContent(const QFileInfo &value)
{
    content.type = IResponseContent::File;
    content.contentFilePath = value.absoluteFilePath();
}

void IWebCore::IResponseWareRaw::setContent(const QFile &file)
{
    content.type = IResponseContent::File;
    content.contentFilePath = QFileInfo(file).absoluteFilePath();
}

void IWebCore::IResponseWareRaw::setFileContent(const QString &filePath)
{
    content.type = IResponseContent::File;
    content.contentFilePath = filePath;
}

// TODO: 这里计算 将 QString 和 QByteArray 长度等同
int IWebCore::IResponseWareRaw::getContentLength()
{
    return content.length();
}
