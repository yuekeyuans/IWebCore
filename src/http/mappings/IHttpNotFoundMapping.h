#pragma once

#include "http/mappings/IHttpMappingInterface.h"
#include "http/mappings/IHttpNotFoundAction.h"

$PackageWebCoreBegin

class IHttpNotFoundMapping : public IHttpMappingInterface<IHttpNotFoundMapping>
{
public:
    IHttpNotFoundMapping() = default;

public:
    virtual void travelPrint() const final;
    virtual IHttpAction *getAction(IRequest &request) const final;

private:
    virtual double $order() const final;

private:
    IHttpNotFoundAction m_action;
};

$PackageWebCoreEnd
