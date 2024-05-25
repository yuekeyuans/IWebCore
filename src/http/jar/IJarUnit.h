#pragma once

#include "core/base/IHeaderUtil.h"

$PackageWebCoreBegin

class IRequestRaw;

class IJarUnit
{
public:
    IJarUnit(IRequestRaw* m_raw);
    virtual bool isValid() const;

protected:
    friend class IRequestRaw;
    IRequestRaw* m_raw{nullptr};
};

$PackageWebCoreEnd
