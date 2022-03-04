#pragma once

#include "base/IHeaderUtil.h"
#include "orm/tableview/IOrmEntityInfoWare.h"

$PackageWebCoreBegin

class IOrmTableInfo : public IOrmEntityInfoWare
{
    $UseWare
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
