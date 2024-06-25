#pragma once

#include "core/base/IHeaderUtil.h"

$PackageWebCoreBegin

class IHttpParameterRestrictInterface;
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
    QString getError();

public:
    int paramTypeId;
    QString paramTypeName;
    QString paramName;
    IStringView paramNameView;

    Position position{Mixed};
    bool optional{false};
    QVector<IHttpParameterRestrictInterface*> restricts;

private:
    QString m_error;
};

$PackageWebCoreEnd
