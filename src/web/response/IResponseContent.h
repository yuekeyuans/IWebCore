#pragma once

#include "core/base/IHeaderUtil.h"
#include <array>

$PackageWebCoreBegin

// 保存 content

struct IResponseContent
{
public:
    enum Type{
        String,
        Bytes,
        File,
        Error,
    };

public:
    void append(const QString& content);
    void append(const QByteArray& content);
    void append(QByteArray&& content);
    void append(const char* content);

    void setContent(QString&& content);
    void setContent(const QString& content);
    void setContent(QByteArray&& content);
    void setContent(const QByteArray& content);
    void setContent(const char* content);

    QByteArray getAsBytes();

public:
    Type type{Type::Bytes};
    QString contentString;
    QByteArray contentBytes;
    QString contentFilePath;
};

$PackageWebCoreEnd
