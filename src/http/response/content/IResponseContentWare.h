#pragma once

#include "core/util/IHeaderUtil.h"

$PackageWebCoreBegin

class IRequest;
class IResponseContentWare
{
public:
    IResponseContentWare() = default;
    virtual ~IResponseContentWare() = default;

public:
    virtual int getSize() = 0;
    virtual IStringView getType() = 0;
    virtual IStringView getContent() = 0;
    virtual IStringView getSuggestedMime() = 0;
};

$PackageWebCoreEnd
