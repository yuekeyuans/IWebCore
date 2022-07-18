#include "IResponseContent.h"
#include "base/IFileUtil.h"

$PackageWebCoreBegin

void IResponseContent::append(const QString &content)
{
    switch (type) {
    case Bytes:
        contentBytes.append(content.toUtf8());
        break;
    case String:
        contentString.append(content);
        break;
    default:
        return;
    }
}

void IResponseContent::append(const QByteArray &content)
{
    switch (type) {
    case Bytes:
        contentBytes.append(content);
        break;
    case String:
        contentString.append(content);
        break;
    default:
        // NOTE: 理论上这里应该报错，但是又不太合逻辑，再等等，再想想
        return;
    }
}

void IResponseContent::append(const char *content)
{
    append(QByteArray(content));
}

void IResponseContent::setContent(QString &&content)
{
    type = Type::String;
    std::swap(contentString, content);
}

void IResponseContent::setContent(const QString &content)
{
    this->type = Type::String;
    contentString = content;
}

void IResponseContent::setContent(QByteArray &&content)
{
    type = Type::Bytes;
    std::swap(contentBytes, content);
}

void IResponseContent::setContent(const QByteArray &content)
{
    type = Type::Bytes;
    contentBytes = content;
}

void IResponseContent::setContent(const char *content)
{
    setContent(QByteArray(content));
}

QByteArray IResponseContent::getAsBytes()
{
    switch(type){
    case Bytes:
        return contentBytes;
    case String:
        return contentString.toUtf8();
    case File:
        return IFileUtil::readFileAsByteArray(contentFilePath);
    }
    return {};
}

$PackageWebCoreEnd
