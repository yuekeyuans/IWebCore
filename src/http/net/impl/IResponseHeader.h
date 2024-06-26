﻿#pragma once

#include "core/util/IHeaderUtil.h"

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
    QStringList values();

private:
    IResponseRaw* m_raw;
    const QString m_key;
};

$PackageWebCoreEnd
