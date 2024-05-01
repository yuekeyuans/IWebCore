#pragma once

#include "core/base/IHeaderUtil.h"

$PackageWebCoreBegin

struct IResponseRaw;
class IResponseHeaderRef
{
public:
    IResponseHeaderRef(IResponseRaw* raw, const QString& key, const QString& value);

public:
    operator QString() noexcept;
    const IResponseHeaderRef& operator=(const QString& value);

private:
    QString m_key;
    QString m_value;
    IResponseRaw* m_raw;
};

$PackageWebCoreEnd
