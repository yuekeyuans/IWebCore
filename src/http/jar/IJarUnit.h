#pragma once

#include "core/util/IHeaderUtil.h"

$PackageWebCoreBegin

class IRequestRaw;

class IJarUnit
{
    friend class IRequestRaw;
public:
    IJarUnit(IRequestRaw* m_raw);
    virtual bool isValid() const;

protected:
    IRequestRaw* m_raw{nullptr};
};

$PackageWebCoreEnd
