#pragma once

#include "core/base/IHeaderUtil.h"

$PackageWebCoreBegin

struct IResponseRaw;
class IResponseHeader
{
public:
    IResponseHeader(IResponseRaw* raw, const QString& key);

public:
    operator QString() noexcept;
    const IResponseHeader& operator=(const QString& value);
    QString key();
    QString value();
    QList<QString> values();

private:
    IResponseRaw* m_raw{};
    QString m_key;
};

$PackageWebCoreEnd
