#pragma once

#include "base/IHeaderUtil.h"

$PackageWebCoreBegin

class IOrmEntityInfoWare    // TODO: the name may be should change.
{
public:
    enum EntityType{
        Table,
        View
    };

public:
    IOrmEntityInfoWare() = default;
    explicit IOrmEntityInfoWare(const QMetaObject& meta);

    QString getFieldSqlType(const QString& fieldName) const;
    QString getFieldTypeName(const QString& fieldName) const;
    QMetaType::Type getFieldTypeId(const QString& fieldName) const;

public:
    QString className;
    QString entityName;
    EntityType entityType{Table};

    QStringList fieldNames;
    QStringList fieldTypeNames;
    QVector<QMetaType::Type> fieldTypeIds;
    QMap<QString, QString> sqlType;
};

$PackageWebCoreEnd

