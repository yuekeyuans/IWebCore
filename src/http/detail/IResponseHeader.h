#pragma once

#include "core/util/IHeaderUtil.h"

$PackageWebCoreBegin


// TODO: 补充 operator=
class IResponseRaw;
class IResponseHeader
{
public:
    IResponseHeader(IResponseRaw& raw, const IString& key);

public:
    operator IStringView() noexcept;
//    const IResponseHeader& operator=(const IString& value);
    IStringView key();
    IStringView value();

private:
    IResponseRaw& m_raw;
    IString m_key;
};

$PackageWebCoreEnd
