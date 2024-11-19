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

protected:
    IRequest* m_request{};
};

// TODO: 这个是否需要放置在 getContent 中传递?
inline void IResponseContentWare::setRequest(IRequest * request)
{
    m_request = request;
}

$PackageWebCoreEnd
