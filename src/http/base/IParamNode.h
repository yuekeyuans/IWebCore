#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/util/ISpawnUtil.h"

$PackageWebCoreBegin

class IHttpParameterRestrictInterface;

struct IParamNode
{
    enum Position{
        Mixed, Param, Url, Header, Body, Content, Cookie, Session,
    };

    int paramTypeId;
    QString paramTypeName;
    QString paramNameRaw;
    QString paramName;
    IStringView paramNameView;

    Position position{Mixed};
    bool optional{false};
    QVector<IHttpParameterRestrictInterface*> restricts;
};

$PackageWebCoreEnd
