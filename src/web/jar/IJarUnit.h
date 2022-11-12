#pragma once

#include "base/IHeaderUtil.h"

$PackageWebCoreBegin

class IReqRespRaw;

class IJarUnit
{
public:
    IJarUnit(IReqRespRaw* m_raw);
    virtual bool isValid() const;

protected:
    friend class IReqRespRaw;
    IReqRespRaw* m_raw{nullptr};
};

$PackageWebCoreEnd
