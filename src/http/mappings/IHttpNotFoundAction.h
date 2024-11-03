#pragma once

#include "http/mappings/IHttpAction.h"

$PackageWebCoreBegin

class IHttpNotFoundAction : public IHttpAction
{
public:
    IHttpNotFoundAction() = default;

public:
    virtual void invoke(IRequest &request) const final;
};


$PackageWebCoreEnd

