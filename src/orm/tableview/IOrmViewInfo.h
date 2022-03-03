#pragma once

#include "base/IHeaderUtil.h"

$PackageWebCoreBegin

class IOrmViewInfo
{
public:
    IOrmViewInfo() = default;
    explicit IOrmViewInfo(const QMetaObject& meta);

    QString getFieldSqlType(const QString& fieldName) const;
    QString getFieldTypeName(const QString& fieldName) const;
    QMetaType::Type getFieldTypeId(const QString& fieldName) const;

};


$PackageWebCoreEnd
