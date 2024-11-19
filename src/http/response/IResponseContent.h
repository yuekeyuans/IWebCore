#pragma once

#include "core/util/IHeaderUtil.h"
#include "http/invalid/IHttpInvalidWare.h"
//#include "http/invalid/IHttpInvalidUnit.h"
#include <array>

$PackageWebCoreBegin

struct IResponseContent
{
public:
    enum class Type{
        Empty,
        String,
        Bytes,
        File,
        Invalid,
    };

public:
    void append(const QString& content);
    void append(const QByteArray& content);
    void append(const char* content);

    void setContent(QString&& content);
    void setContent(const QString& content);
    void setContent(QByteArray&& content);
    void setContent(const QByteArray& content);
    void setContent(const char* content);
    void setContent(IHttpInvalidWare ware);

    QByteArray getAsBytes();

public:
    Type type{Type::Empty};
    QString contentString;
    QByteArray contentBytes;
    std::function<void(IRequest&)> invalidFunction{};
};

$PackageWebCoreEnd
