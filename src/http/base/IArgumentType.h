#pragma once

#include "core/util/IHeaderUtil.h"

$PackageWebCoreBegin

class IHttpParameterRestrictInterface;

class IRequest;
struct IArgumentType
{
public:
    void* create(IRequest&) const;
    void destory(void*) const;

public:
    enum Position{
        Auto, Param, Url, Header, Body, Content, Cookie, Session,
    };

public:
    QMetaType::Type typeId{QMetaType::UnknownType};
    QString typeName;

    QString nameRaw;
    QString name;

    Position position{Auto};
    bool optional{false};
    QVector<IHttpParameterRestrictInterface*> restricts;
};

$PackageWebCoreEnd
