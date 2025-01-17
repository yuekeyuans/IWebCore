﻿#include "IHttpNotFoundAction.h"
#include "http/invalid/IHttpNotFoundInvalid.h"
#include "http/IRequest.h"

$PackageWebCoreBegin

void IHttpNotFoundAction::invoke(IRequest &request) const
{
    request.setInvalid(IHttpNotFoundInvalid());
    request.startWrite();
}

$PackageWebCoreEnd
