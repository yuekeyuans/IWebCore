#pragma once

#include "base/IHeaderUtil.h"

$PackageWebCoreBegin

class IOrmTableInfo
{

public:
    IOrmTableInfo() = default;
    explicit IOrmTableInfo(const QMetaObject& meta);

    QString getFieldSqlType(const QString& fieldName) const;
    QString getFieldTypeName(const QString& fieldName) const;
    QMetaType::Type getFieldTypeId(const QString& fieldName) const;

public:
    QString className;
    QString tableName;

    QStringList fieldNames;
    QStringList fieldTypeNames;
    QVector<QMetaType::Type> fieldTypeIds;
    QMap<QString, QString> sqlType;

    QString primaryKey;
    QString autoGenerateKey;
    QString autoGenerateType;
    QStringList notNullNKeys;
    QStringList uniqueKeys;
};

$PackageWebCoreEnd
