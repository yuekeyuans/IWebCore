#pragma once

#include "http/mappings/IHttpActionInterface.h"

$PackageWebCoreBegin

class IHttpOptionsMethodAction : public IHttpActionInterface<IHttpOptionsMethodAction>
{
public:
    IHttpOptionsMethodAction() = default;

public:
    virtual void invoke(IRequest &request) const final;

private:
    void processUrlOptions(IRequest&) const;

private:
    inline static const IString AllowContent = "GET, HEAD, POST, PUT, DELETE, PATCH, OPTIONS";
};

$PackageWebCoreEnd
