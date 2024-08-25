#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/config/IContextTaskInterface.h"
#include "core/config/IConfigPreProcessor.h"

$PackageWebCoreBegin

class IContextSystemVariableTask : public IContextTaskInterface<IContextSystemVariableTask, false>
{
public:
    virtual IJson config();

private:
    IJson getSystemEnvironment();
};

$PackageWebCoreEnd

