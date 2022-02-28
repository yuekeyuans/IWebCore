#pragma once

#include "base/IHeaderUtil.h"

$PackageWebCoreBegin

class IRequest;
class IResponse;

class IRequestPreProcessInterface
{
public:
    virtual bool match(const IRequest& request) = 0;
    virtual void process(IRequest& request, IResponse& response) = 0;
};

$PackageWebCoreEnd
