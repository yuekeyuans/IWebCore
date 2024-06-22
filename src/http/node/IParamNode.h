#pragma once

#include "core/base/IHeaderUtil.h"

$PackageWebCoreBegin

struct IParamNode
{
    enum Position{
        Mixed,
        Param,
        Url,
        Header,
        Body,
        Content,
        Cookie,
        Session,
    };

public:
    IParamNode(int paramTypeId, QString paramTypeName, QString paramName);
public:
    int paramTypeId;
    QString paramTypeName;
    QString paramName;
    QStringList paramQualifiers;
    Position position{Mixed};
    bool nullable{false};
};

$PackageWebCoreEnd
