#pragma once

#include "core/util/IHeaderUtil.h"

$PackageWebCoreBegin

class IRequestImpl;
class IJarUnit
{
    friend class IRequestImpl;
public:
    IJarUnit(IRequestImpl& m_raw);
//    virtual bool isValid() const;

protected:
    IRequestImpl& m_raw;
};

$PackageWebCoreEnd
