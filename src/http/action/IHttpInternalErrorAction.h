#pragma once

#include "http/action/IHttpActionInterface.h"

$PackageWebCoreBegin

class IHttpInternalErrorAction : public IHttpActionInterface<IHttpInternalErrorAction>
{
public:
    IHttpInternalErrorAction() = default;

public:
    virtual void invoke(IRequest &request) const final;
};

$PackageWebCoreEnd
