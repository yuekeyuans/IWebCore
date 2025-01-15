#pragma once

#include "http/action/IHttpActionInterface.h"

$PackageWebCoreBegin

class IHttpNotFoundAction : public IHttpActionInterface<IHttpNotFoundAction>
{
public:
    IHttpNotFoundAction() = default;

public:
    virtual void invoke(IRequest &request) const final;
};

$PackageWebCoreEnd

