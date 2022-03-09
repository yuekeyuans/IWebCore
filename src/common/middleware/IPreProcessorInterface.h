#pragma once

#include "base/IHeaderUtil.h"
#include "common/middleware/IProcessorWare.h"

$PackageWebCoreBegin

template<typename T, bool enabled=true>
class IPreProcessorInterface : public IProcessorWare
{
public:
    IPreProcessorInterface() = default;

    virtual bool match(IRequest& request, IResponse& response) override = 0;
    virtual bool action(IRequest& request, IResponse& response) override = 0;
};

$PackageWebCoreEnd
