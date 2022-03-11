#pragma once

#include "base/IHeaderUtil.h"
#include "common/middleware/IPreProcessorInterface.h"
#include "common/middleware/IMiddleWarePreProcessor.h"

$PackageWebCoreBegin

class ICookiePreProcessor : public IPreProcessorInterface<ICookiePreProcessor>
{
    $AsMiddleWare(ICookiePreProcessor)
public:
    ICookiePreProcessor() = default;

    virtual bool match(IRequest& request, IResponse& response) final;
    virtual bool action(IRequest& request, IResponse& response) final;
};

$PackageWebCoreEnd
