#pragma once
#include "base/IHeaderUtil.h"

$PackageWebCoreBegin

class IResponse;
class IRequest;
class IResponsePostProcessInterface
{
public:
    IResponsePostProcessInterface();
    bool match(const IRequest& request, const IResponse&);
    void process(IRequest& request, IResponse& response);
};

$PackageWebCoreEnd
