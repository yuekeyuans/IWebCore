#pragma once

#include "http/mappings/IHttpActionInterface.h"

$PackageWebCoreBegin

class IHttpInternalErrorAction : public IHttpActionInterface
{
public:
    IHttpInternalErrorAction();

    // IHttpAction interface
public:
    virtual void invoke(IRequest &request) const final;
};

$PackageWebCoreEnd
