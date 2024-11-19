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
    void setRequest(IRequest*);

public:
    virtual int getSize() = 0;
    virtual const char* getType() = 0;
    virtual IStringView getContent() = 0;
    virtual QString getSuggestedMime() = 0;
};

$PackageWebCoreEnd
