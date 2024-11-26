#pragma once

#include "core/util/IHeaderUtil.h"
#include "http/invalid/IHttpInvalidInterface.h"

$PackageWebCoreBegin

class IHttpBadRequestInvalid : public IHttpInvalidInterface<IHttpBadRequestInvalid>
{
public:
    IHttpBadRequestInvalid();
    IHttpBadRequestInvalid(const std::string& description);

public:
    virtual void process(const IHttpInvalidWare&, IResponseRaw&) final;
};

$PackageWebCoreEnd
