#pragma once

#include "core/base/IHeaderUtil.h"
#include "http/biscuits/IHttpStatus.h"

$PackageWebCoreBegin

// TODO: check lvalue swap work or not!!!

struct IHttpInvalidWare
{
public:
    IHttpInvalidWare() = default;
    explicit IHttpInvalidWare(IHttpStatusCode status, const QString& name_, const QString& description_="");

public:
    bool invalid{false};
    IHttpStatusCode status{IHttpStatus::UNKNOWN};
    QString name;
    QString description;
};

$PackageWebCoreEnd
