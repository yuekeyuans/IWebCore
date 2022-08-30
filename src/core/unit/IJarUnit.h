#pragma once

#include "base/IHeaderUtil.h"

$PackageWebCoreBegin

class IReqRespRaw;

class IJarUnit
{
public:
    IJarUnit() = default;
    virtual bool isValid() const = 0;

public:
    void setReqRespRaw(IReqRespRaw* raw);

protected:
    friend class IReqRespRaw;
    IReqRespRaw* raw{nullptr};
};

$PackageWebCoreEnd
