﻿#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/application/IApplicationInterface.h"

$PackageWebCoreBegin

class IQtApplication : public QCoreApplication, public IApplicationInterface
{
public:
    explicit IQtApplication(int argc, char** argv);

public:
    virtual int run() final;
};

$PackageWebCoreEnd
