#pragma once

#include "base/IHeaderUtil.h"

$PackageWebCoreBegin

class IReqRespRaw;

class IJarUnit
{
public:
    inline IJarUnit(IReqRespRaw* m_raw);
    virtual bool isValid() const = 0;

protected:
    friend class IReqRespRaw;
    IReqRespRaw* m_raw{nullptr};
};

IJarUnit::IJarUnit(IReqRespRaw* raw){
    this->m_raw = raw;
}

$PackageWebCoreEnd
