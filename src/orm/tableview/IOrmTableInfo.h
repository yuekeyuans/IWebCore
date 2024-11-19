#pragma once

#include "core/util/IHeaderUtil.h"
#include "orm/tableview/IOrmEntityInfoWare.h"

$PackageWebCoreBegin

class IOrmTableInfo : public IOrmEntityInfoWare
{
public:
    IOrmTableInfo() = default;
    explicit IOrmTableInfo(const QMetaObject& meta);

public:
    QString primaryKey;
    QString autoGenerateKey;
    QString autoGenerateType;
    QStringList notNullNKeys;
    QStringList uniqueKeys;
};

$PackageWebCoreEnd
