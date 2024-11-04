#pragma once

#include "core/util/IHeaderUtil.h"
#include "http/invalid/IHttpInvalidInterface.h"

$PackageWebCoreBegin

class IHttpBadRequestInvalid : public IHttpInvalidInterface<IHttpBadRequestInvalid>
{
public:
    IHttpBadRequestInvalid();
    IHttpBadRequestInvalid(const QString& description);

public:
    virtual void process(IRequest&) final;
};

$PackageWebCoreEnd
