#pragma once

#include "http/mappings/IHttpActionInterface.h"

$PackageWebCoreBegin

// this is designed for invalid request;
class IHttpInvalidRequestAction : public IHttpActionInterface<IHttpInvalidRequestAction>
{
public:
    IHttpInvalidRequestAction() = default;

public:
    virtual void invoke(IRequest &request) const final;
};

$PackageWebCoreEnd
