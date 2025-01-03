#pragma once

#include "core/util/IHeaderUtil.h"

$PackageWebCoreBegin

class IResponseRaw;
class IResponseHeader
{
public:
    IResponseHeader(IResponseRaw& raw, const IString& key);

public:
    operator const IString&() noexcept;
    const IResponseHeader& operator=(const IString& value);
    const IString& key();
    const IString& value();

private:
    IResponseRaw& m_raw;
    const IString& m_key;
};

$PackageWebCoreEnd
