#pragma once

#include "core/base/IHeaderUtil.h"
#include "http/invalid/IHttpInvalidUnit.h"

$PackageWebCoreBegin

class IRequest;
class IResponse;
class IHttpInvalidWare : public IHttpInvalidUnit
{
public:
    using IHttpInvalidUnit::IHttpInvalidUnit;
    virtual ~IHttpInvalidWare() = default;

public:
    virtual void process(IRequest&, IResponse&);
};

$PackageWebCoreEnd
