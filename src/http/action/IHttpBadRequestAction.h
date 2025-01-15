#pragma once

#include "http/action/IHttpActionInterface.h"

$PackageWebCoreBegin

class IHttpBadRequestAction : public IHttpActionInterface<IHttpBadRequestAction>
{
public:
    IHttpBadRequestAction() = default;

public:
    virtual void invoke(IRequest& request) const final;
};

$PackageWebCoreEnd
