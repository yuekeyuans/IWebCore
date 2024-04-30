#pragma once

#include "core/base/IHeaderUtil.h"
#include "http/biscuits/IHttpStatus.h"

$PackageWebCoreBegin

struct IHttpInvalidUnit
{
public:
    IHttpInvalidUnit() = default;
    explicit IHttpInvalidUnit(IHttpStatusCode status, const QString& tag, const QString& description="");

public:
    IHttpStatusCode status{IHttpStatus::UNKNOWN};
    QString tag;
    QString description;
};

$PackageWebCoreEnd
