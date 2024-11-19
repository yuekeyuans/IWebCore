#pragma once

#include "core/util/IHeaderUtil.h"

$PackageWebCoreBegin

class IRequest;
class IHttpAction
{
public:
    IHttpAction() = default;
    virtual ~IHttpAction() = default;

public:
    virtual void invoke(IRequest& request) const = 0;

public:
    bool m_autoRecycle{false};    // auto recycle after used
};

//using IHttpActionInterface = IHttpAction;

$PackageWebCoreEnd
