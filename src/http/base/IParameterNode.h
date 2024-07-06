#pragma once

#include "core/util/IHeaderUtil.h"

$PackageWebCoreBegin

class IHttpParameterRestrictInterface;

struct IParameterNode
{
    enum Position{
        Mixed, Param, Url, Header, Body, Content, Cookie, Session,
    };

    int typeId;
    QString typeName;
    QString nameRaw;
    QString name;

    Position position{Mixed};
    bool optional{false};
    QVector<IHttpParameterRestrictInterface*> restricts;
};

$PackageWebCoreEnd
