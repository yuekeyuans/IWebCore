#pragma once

#include "base/IHeaderUtil.h"
#include <array>

$PackageWebCoreBegin

// 保存 content

struct IResponseContent
{
public:
    enum Type{
        String,
        Bytes,
        File
    };

public:
    int length();
    void append(const QString& content);
    void append(const QByteArray& content);
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


    //extend
    // TODO: 这个内容是以后使用的， 目的是返回一部分内容
    std::array<int, 2> anc{-1, -1};
};

$PackageWebCoreEnd
