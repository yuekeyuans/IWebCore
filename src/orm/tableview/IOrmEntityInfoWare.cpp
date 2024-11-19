#include "IOrmEntityInfoWare.h"
#include "core/util/IMetaUtil.h"

#include "orm/tableview/IOrmTableInfo.h"
#include "orm/tableview/IOrmViewInfo.h"

$PackageWebCoreBegin

namespace IOrmEntityInfoWareHelper{
    void obtainFieldInfo(const QMetaObject& staticMetaObject, IOrmEntityInfoWare& tableInfo);
}

IOrmEntityInfoWare::IOrmEntityInfoWare(const QMetaObject &meta)
{
    auto clsInfo = IMetaUtil::getMetaClassInfoMap(meta);
    this->className = meta.className();
    this->entityName = IMetaUtil::getMetaClassInfoByName(meta, "orm_entityName");

    auto entityTypeName = clsInfo["orm_entityType"];
    this->entityType = (entityTypeName == "table") ? Table : View;

    IOrmEntityInfoWareHelper::obtainFieldInfo(meta, *this);
}

QString IOrmEntityInfoWare::getFieldSqlType(const QString& fieldName) const
{
    if(sqlType.contains(fieldName)){
        return sqlType[fieldName];
    }
    return "";
}

QString IOrmEntityInfoWare::getFieldTypeName(const QString& fieldName) const
{
    auto index = fieldNames.indexOf(fieldName);
    return fieldTypeNames[index];
}

QMetaType::Type IOrmEntityInfoWare::getFieldTypeId(const QString &fieldName) const
{
    auto index = fieldNames.indexOf(fieldName);
    if(index == -1){
        return QMetaType::UnknownType;
    }
    return fieldTypeIds[index];
}

void IOrmEntityInfoWareHelper::obtainFieldInfo(const QMetaObject& staticMetaObject, IOrmEntityInfoWare& tableInfo){
    auto metaProperties =IMetaUtil::getMetaProperties(staticMetaObject);
    for(const QMetaProperty& property : metaProperties){
        tableInfo.fieldNames.append(property.name());
        tableInfo.fieldTypeNames.append(property.typeName());
        tableInfo.fieldTypeIds.append(QMetaType::Type(static_cast<int>(property.type())));
    }
}

$PackageWebCoreEnd
