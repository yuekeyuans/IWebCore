#pragma once

#include "core/util/IHeaderUtil.h"
#include "http/invalid/IHttpInvalidInterface.h"
#include "http.h"

$PackageWebCoreBegin

class IHttpNotFoundInvalid : public IHttpInvalidInterface<IHttpNotFoundInvalid>
{
public:
    IHttpNotFoundInvalid();
    IHttpNotFoundInvalid(QString description);

public:
    virtual void process(IRequest&) final;
};

$PackageWebCoreEnd
