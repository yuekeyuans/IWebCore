#pragma once

#include "base/IHeaderUtil.h"
#include "common/middleware/IPostProcessorInterface.h"
#include "common/middleware/IMiddleWarePreProcessor.h"

$PackageWebCoreBegin

class ICookiePostProcessor : public IPostProcessorInterface<ICookiePostProcessor>
{
    $AsMiddleWare(ICookiePostProcessor)
public:
    ICookiePostProcessor() = default;

    virtual bool match(IRequest& request, IResponse& response) final;
    virtual bool action(IRequest& request, IResponse& response) final;
};

$PackageWebCoreEnd
