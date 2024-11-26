#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/base/IStringData.h"

$PackageWebCoreBegin

class IRequest;
class IResponseContentWare
{
    friend class IResponseRaw;
public:
    IResponseContentWare() = default;
    virtual ~IResponseContentWare();

public:
    virtual int getSize() = 0;
    virtual IStringView getType() = 0;
    virtual IStringView getContent() = 0;
    virtual IStringView getSuggestedMime() = 0;

protected:
    IResponseContentWare* m_excess{};
};

inline IResponseContentWare::~IResponseContentWare()
{
    if(m_excess){
        delete m_excess;
        m_excess = nullptr;
    }
}

$PackageWebCoreEnd
