#include "IResponseContent.h"
#include "core/base/IFileUtil.h"
#include "http/IHttpAssert.h"

$PackageWebCoreBegin

namespace detail
{
    inline static QString getTypename(IResponseContent::Type type)
    {
        QStringList typeString = {
            "Empty", "String", "Bytes", "File", "Invalid",
        };
        return typeString[(int)type];
    }
}

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
        contentString.append(content);
        break;
    default:
        $Ast->warn("response_incorrect_append", "current type is " + detail::getTypename(type));
        return;
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
        contentString.append(content);
        break;
    default:
        $Ast->warn("response_incorrect_append", "current type is " + detail::getTypename(type));
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

void IResponseContent::setContent(IHttpInvalidUnit ware)
{
    type = Type::Invalid;
    contentInvalid = ware;
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
        return IFileUtil::readFileAsByteArray(contentString);
    case Type::Invalid:
        $Ast->fatal("response_invalid_type_error");
    }
    return {};
}

$PackageWebCoreEnd
