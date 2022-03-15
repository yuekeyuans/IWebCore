#pragma once

#include "base/IHeaderUtil.h"
#include "common/middleware/IPreProcessorInterface.h"
#include "common/middleware/IMiddleWarePreProcessor.h"
#include "base/IConstantUtil.h"

$PackageWebCoreBegin

class IServerNameMiddleWare : public IPreProcessorInterface<IServerNameMiddleWare, IConstantUtil::IServerNameMiddleWareEnabeld>
{
    $AsMiddleWare(IServerNameMiddleWare)
public:
    IServerNameMiddleWare();

    virtual bool match(IRequest& request, IResponse& response) final;
    virtual bool action(IRequest& request, IResponse& response) final;
};

$PackageWebCoreEnd
