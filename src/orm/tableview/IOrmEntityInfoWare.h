#pragma once

#include "base/IHeaderUtil.h"

$PackageWebCoreBegin

class IOrmTableInfo;
class IOrmViewInfo;

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

    virtual QString getFieldSqlType(const QString& fieldName) const;
    virtual QString getFieldTypeName(const QString& fieldName) const;
    virtual QMetaType::Type getFieldTypeId(const QString& fieldName) const;

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

