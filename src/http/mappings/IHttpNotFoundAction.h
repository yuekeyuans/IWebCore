#pragma once

#include "http/mappings/IHttpActionInterface.h"

$PackageWebCoreBegin

class IHttpNotFoundAction : public IHttpActionInterface<IHttpNotFoundAction>
{
public:
    IHttpNotFoundAction() = default;

public:
    virtual void invoke(IRequest &request) const final;
};

$PackageWebCoreEnd

