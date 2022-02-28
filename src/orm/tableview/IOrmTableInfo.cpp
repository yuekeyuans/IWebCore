#include "IOrmTableInfo.h"

#include "base/IConstantUtil.h"
#include "orm/IOrmManage.h"

$PackageWebCoreBegin

IOrmTableInfo::IOrmTableInfo(const QMetaObject &meta)
{
    load(meta);
}

QString IOrmTableInfo::getFieldSqlType(const QString& fieldName) const
{
    if(sqlType.contains(fieldName)){
        return sqlType[fieldName];
    }
    return "";
}

QString IOrmTableInfo::getFieldTypeName(const QString& fieldName) const
{
    auto index = fieldNames.indexOf(fieldName);
    return fieldTypeNames[index];
}

QMetaType::Type IOrmTableInfo::getFieldTypeId(const QString &fieldName) const
{
    auto index = fieldNames.indexOf(fieldName);
    if(index == -1){
        return QMetaType::UnknownType;
    }
    return fieldTypeIds[index];
}

void IOrmTableInfo::load(const QMetaObject &staticMetaObject)
{

    auto& m_tableInfo = *this;
    auto metaClassInfo = IMetaUtil::getMetaClassInfoMap(staticMetaObject);

    m_tableInfo.className = staticMetaObject.className();
    m_tableInfo.tableName = IMetaUtil::getMetaClassInfoByName(metaClassInfo, "orm_tableName");

    auto metaProperties =IMetaUtil::getMetaProperties(staticMetaObject);
    for(const QMetaProperty& property : metaProperties){
        m_tableInfo.fieldNames.append(property.name());
        m_tableInfo.fieldTypeNames.append(property.typeName());
        m_tableInfo.fieldTypeIds.append(QMetaType::Type(static_cast<int>(property.type())));
    }

    for(auto name : metaClassInfo.keys()){
        if(name.startsWith(IConstantUtil::Sql_PrimayKeyClause)){
            m_tableInfo.primaryKey = metaClassInfo[name];
        }
        if(name.startsWith(IConstantUtil::Sql_UniqueKeyClause)){
            m_tableInfo.uniqueKeys.append(metaClassInfo[name]);
        }
        if(name.startsWith(IConstantUtil::Sql_NotNulKeyClause)){
            m_tableInfo.notNullNKeys.append(metaClassInfo[name]);
        }
        if(name.startsWith(IConstantUtil::Sql_AutoGenerateKeyClause)){
            m_tableInfo.autoGenerateKey = metaClassInfo[name];
        }
        if(name.startsWith(IConstantUtil::Sql_SqlTypeKeyClause)){
            auto fieldName = name.mid(QString(IConstantUtil::Sql_SqlTypeKeyClause).length());
            m_tableInfo.sqlType[fieldName] = metaClassInfo[name];
        }
    }

    if(!m_tableInfo.autoGenerateKey.isEmpty()){
        QString name = QString(IConstantUtil::Sql_AutoGenerateTypeClause).append(m_tableInfo.autoGenerateKey);
        m_tableInfo.autoGenerateType = metaClassInfo[name];
    }
    m_tableInfo.checkInfo(metaClassInfo);
}

void IOrmTableInfo::checkInfo(const QMap<QString, QString> &clsInfo)
{
    checkFieldTypes(clsInfo);
    checkDuplicatedPrimaryKey(clsInfo);
    checkAutoGenerateInfo(clsInfo);
}

void IOrmTableInfo::checkFieldTypes(const QMap<QString, QString> &clsInfo)
{
    Q_UNUSED(clsInfo)

    static QList<QMetaType::Type> allowTypes ={
        QMetaType::Bool,
        QMetaType::QString,
        QMetaType::Char, QMetaType::UChar,
        QMetaType::Short, QMetaType::UShort,
        QMetaType::Int, QMetaType::UInt,
        QMetaType::Long, QMetaType::ULong,
        QMetaType::LongLong, QMetaType::ULongLong,
        QMetaType::Double, QMetaType::Float,
        QMetaType::QDate, QMetaType::QTime, QMetaType::QDateTime,
    };
    for(const auto& typeId : fieldTypeIds){
        if(!allowTypes.contains(typeId)){
            QString info = QString("this kind of type is not supported in table, please change to the supported type. \n"
                                   "Type : ").append(QMetaType::typeName(typeId));
            qFatal(info.toUtf8());
        }
    }
}

void IOrmTableInfo::checkDuplicatedPrimaryKey(const QMap<QString, QString> &clsInfo)
{
    int index = 0;
    for(auto key : clsInfo.keys()){
        if(key.startsWith("primaryKey__")){
           index ++;
        }
    }
    if(index == 0){
        QString info = className + " table has no primary key, please add a primary key";
        qFatal(info.toUtf8());
    }else if(index > 1){
        QString info = className + " table has more than one primary key, one table can only has one primary key";
        qFatal(info.toUtf8());
    }
    auto pos = fieldNames.indexOf(primaryKey);
    auto typeId = fieldTypeIds[pos];
    if(!IToeUtil::isPrimaryKeyType(typeId)){
        QString info = className + " table has incorrect primary key annotated type. \n"
                                   "the only allowed type is int, long, longlong/int64, QString\n"
                                   "field:" + fieldNames[pos] + " type:" + fieldTypeNames[pos];
        qFatal(info.toUtf8());
    }
    if(typeId != QMetaType::QString && typeId != QMetaType::LongLong){
        QString info = QString("primary key that is number type recommended is qlonglong/qint64 type.\n"
                               "current is ").append(QMetaType::typeName(typeId)).append(" in class ").append(className);
        qWarning() << info;
    }
}

void IOrmTableInfo::checkAutoGenerateInfo(const QMap<QString, QString> &clsInfo)
{
    Q_UNUSED(clsInfo)
    static QList<QMetaType::Type> allowTypes = {
        QMetaType::Int, QMetaType::LongLong, QMetaType::QString
    };

    if(!autoGenerateKey.isEmpty()){
        if(autoGenerateKey != primaryKey){
            QString info = className + " table: auto increment key must equal to primary key";
            qFatal(info.toUtf8());
        }
    }

    int index = 0;
    for(auto key : clsInfo.keys()){
        if(key.startsWith("autoIncrementKey__")){
            index ++;
        }
    }
    if(index >1){
        QString info = className + " table: you can not have more than one increment note, please check";
        qFatal(info.toUtf8());
    }
}

$PackageWebCoreEnd
