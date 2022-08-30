#pragma once

#include "base/IHeaderUtil.h"

$PackageWebCoreBegin

class IReqRespRaw;

class IJarUnit
{
public:
    inline IJarUnit(IReqRespRaw* raw);
    virtual bool isValid() const = 0;

protected:
    friend class IReqRespRaw;
    IReqRespRaw* raw{nullptr};
};

IJarUnit::IJarUnit(IReqRespRaw* raw){
    this->raw = raw;
}

$PackageWebCoreEnd
