#pragma once

#include "core/util/IHeaderUtil.h"

$PackageWebCoreBegin

// TODO: 之后在设计插件功能的时候，这个代码需要重构
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
