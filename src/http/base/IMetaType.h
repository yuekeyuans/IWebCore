#pragma once

#include "core/util/IHeaderUtil.h"

$PackageWebCoreBegin

struct IMetaType
{
public:
    IMetaType() = default;
    IMetaType(QMetaType::Type, const QString& = {});
    bool operator ==(const IMetaType&) const;
    bool operator <(const IMetaType&) const;

public:
    QMetaType::Type typeId{QMetaType::UnknownType};
    QString typeName;
};

$PackageWebCoreEnd
