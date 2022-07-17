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
