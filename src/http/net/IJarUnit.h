#pragma once

#include "core/util/IHeaderUtil.h"

$PackageWebCoreBegin

class IRequest;
class IRequestImpl;
class IJarUnit
{
public:
    IJarUnit();
    IJarUnit(IRequestImpl& impl);
    IJarUnit(IRequest& request);

protected:
    IRequestImpl& m_impl;
};

$PackageWebCoreEnd
