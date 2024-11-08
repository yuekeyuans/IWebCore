#pragma once

#include "core/util/IHeaderUtil.h"

$PackageWebCoreBegin

class IHttpParameterRestrictInterface;

struct IArgumentTypeNode
{
    enum Position{
        Auto, Param, Url, Header, Body, Content, Cookie, Session,
    };

    int typeId;
    QString typeName;
    QString nameRaw;
    QString name;

    Position position{Auto};
    bool optional{false};
    QVector<IHttpParameterRestrictInterface*> restricts;
};

$PackageWebCoreEnd
