﻿#pragma once

#include "core/util/IHeaderUtil.h"
#include "http/invalid/IHttpInvalidUnit.h"

$PackageWebCoreBegin

// TODO: 这个等回来补上具体功能

class IHttpParameterRestrictInterface   // : public ITask...
{
public:
    IHttpParameterRestrictInterface();

public:
    virtual IHttpInvalidUnit invalidUnit() = 0; // 失败时返回
    virtual QString tag() const = 0;
    virtual QStringList supportedTypes() const = 0;
    virtual bool validate(void*) const = 0;
};

$PackageWebCoreEnd
