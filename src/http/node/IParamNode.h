#pragma once

#include "core/base/IHeaderUtil.h"

$PackageWebCoreBegin

class IHttpParameterRestrictInterface;

struct IParamNode
{
    enum Position{
        Mixed, Param, Url, Header, Body, Content, Cookie, Session,
    };

    int paramTypeId;
    QString paramTypeName;
    QString paramName;
    IStringView paramNameView;

    Position position{Mixed};
    bool optional{false};
    QVector<IHttpParameterRestrictInterface*> restricts;
};

namespace IParamNodeHelper
{
    IParamNode createParamNode(int paramTypeId, QString paramTypeName, QString paramName);
}

$PackageWebCoreEnd
