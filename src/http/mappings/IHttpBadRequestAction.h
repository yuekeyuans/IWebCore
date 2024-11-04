#pragma once

#include "http/mappings/IHttpActionInterface.h"

$PackageWebCoreBegin

class IHttpBadRequestAction : public IHttpActionInterface<IHttpBadRequestAction>
{
public:
    IHttpBadRequestAction() = default;

public:
    virtual void invoke(IRequest& request) const final;
};

$PackageWebCoreEnd
