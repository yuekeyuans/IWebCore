#include "IResponseContent.h"
#include "core/util/IFileUtil.h"
#include "core/util/IConstantUtil.h"
#include "core/abort/IAbortInterface.h"

$PackageWebCoreBegin

void IResponseContent::append(const QString &content)
{
    switch (type) {
    case Type::Empty:
        type = Type::String;
        contentString = content;
        break;
    case Type::Bytes:
        contentBytes.append(content.toUtf8());
        break;
    case Type::String:
    case Type::Invalid:
        contentString.append(content);
        break;
    }
}

void IResponseContent::append(const QByteArray &content)
{
    switch (type) {
    case Type::Empty:
        type = Type::Empty;
        contentBytes = content;
        break;
    case Type::Bytes:
        contentBytes.append(content);
        break;
    case Type::String:
    case Type::Invalid:
        contentString.append(content);
        break;
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

void IResponseContent::setContent(IHttpInvalidWare ware)
{
    type = Type::Invalid;
    contentString = ware.description;
    if(ware.m_function){
        invalidFunction = ware.m_function;
    }
}

QByteArray IResponseContent::getAsBytes()
{
    switch(type){
    case Type::Empty:
        return {};
    case Type::Bytes:
        return contentBytes;
    case Type::String:
        return contentString.toUtf8();
    case Type::File:
        if(IConstantUtil::DebugMode){
            IFileUtil::assertWhenFileInvalid(contentString);
        }
        return *IFileUtil::readFileAsByteArray(contentString);  // TODO:
    case Type::Invalid:
        return contentString.toUtf8();  // this maybe ajusted in invalidFunction
    }
    return {};
}

$PackageWebCoreEnd
