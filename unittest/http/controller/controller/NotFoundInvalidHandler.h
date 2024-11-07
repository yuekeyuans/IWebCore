#pragma once

#include "http/invalid/IHttpInvalidHandlerInterface.h"
#include "http/invalid/IHttpNotFoundInvalid.h"

using namespace IWebCore;

class NotFoundInvalidHandler : public IHttpInvalidHandlerInterface<NotFoundInvalidHandler, IHttpNotFoundInvalid, true>
{
public:
    NotFoundInvalidHandler();

public:
    virtual void handle(IRequest&) const;
};

