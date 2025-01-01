#pragma once

#include "http/biscuits/IHttpMethod.h"
#include "http/base/IMethodNode.h"
#include "http/controller/IHttpPath.h"
#include "http/mappings/IHttpActionInterface.h"

$PackageWebCoreBegin

struct IHttpControllerAction : public IHttpActionInterface<IHttpControllerAction>
{
private:
    using ParamType = std::array<void*, 11>;

public:
    virtual void invoke(IRequest &req) const final;

private:
    ParamType createParams(IRequest&) const;
    void destroyParams(const ParamType&) const;

public:
    IHttpMethod httpMethod;
    void* parentNode{};

    IHttpPath route;
    IMethodNode methodNode;
};

$PackageWebCoreEnd
