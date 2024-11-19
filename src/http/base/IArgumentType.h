#pragma once

#include "core/util/IHeaderUtil.h"
#include "IMetaType.h"

$PackageWebCoreBegin

class IHttpParameterRestrictInterface;

class IRequest;
struct IArgumentType : public IMetaType
{
public:
    void* create(IRequest&) const;
    void destory(void*) const;

public:
    enum Position{
        Auto, Param, Url, Header, Body, Content, Cookie, Session,
    };

    QString nameRaw;
    QString name;

    Position position{Auto};
    bool optional{false};
    QVector<IHttpParameterRestrictInterface*> restricts;
};

$PackageWebCoreEnd
