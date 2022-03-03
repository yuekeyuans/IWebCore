#include "IOrmViewInfo.h"

$PackageWebCoreBegin

IOrmViewInfo::IOrmViewInfo(const QMetaObject &meta)
{

}

QString IOrmViewInfo::getFieldSqlType(const QString &fieldName) const
{
    return {};
}

QString IOrmViewInfo::getFieldTypeName(const QString &fieldName) const
{
    return {};
}

QMetaType::Type IOrmViewInfo::getFieldTypeId(const QString &fieldName) const
{
    return {};
}

$PackageWebCoreEnd
