#pragma once

#include "core/util/IHeaderUtil.h"

$PackageWebCoreBegin

class IRequest;
class IRequestImpl;
class IJarUnit
{
//    friend class IRequestImpl;
public:
    IJarUnit();
    IJarUnit(IRequestImpl& m_raw);
    IJarUnit(IRequest&);

protected:
    IRequestImpl& m_raw;
};

$PackageWebCoreEnd
