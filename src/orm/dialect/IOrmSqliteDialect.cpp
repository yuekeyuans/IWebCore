#include "IOrmSqliteDialect.h"
#include "base/IOrmUtil.h"
#include "base/ITicTacUtil.h"
#include "base/IConstantUtil.h"
#include "orm/tableview/IOrmTableInfo.h"
#include "orm/ISqlQuery.h"
#include "orm/IOrmManage.h"
#include "orm/tableview/IOrmEntityWare.h"
#include "orm/tableview/IOrmTableWare.h"

$PackageWebCoreBegin

QString IOrmSqliteDialect::dialectType()
{
    return "QSQLITE";
}

bool IOrmSqliteDialect::insert(QSqlDatabase& db, IOrmTableWare& table, const QStringList &columns)
{
    ISqlQuery query(db);
    const auto info = table.getOrmEntityInfo();
    auto sql = getInsertSqlClause(*info, columns);
    query.prepare(sql);

    for(const auto& fieldName : columns){
        auto originVale = table.getFieldValue(fieldName);
        auto decoratedValue = decorateValue(*info, fieldName, originVale);
        query.bindValue(":" + fieldName, decoratedValue);
    }
    auto result = query.exec();
    if(!result){
        return result;
    }

    if(!info->autoGenerateKey.isEmpty()){
        auto rowid = query.lastInsertId();
        auto key = getInsertedPrimaryKey(db, table, rowid);
        table.setFieldValue(info->autoGenerateKey, key);
    }
    return result;
}

// NOTE: 这是对数据最粗泛的支持，具体的数据需要具体的处理， 需要在各个 dialect 当中重载
QString IOrmSqliteDialect::getSqlType(const int typeId)
{
    static const QMap<int, QString> map = {
        {QMetaType::Char, "INTEGER"},
        {QMetaType::UChar, "INTEGER"},
        {QMetaType::Short, "INTEGER"},
        {QMetaType::UShort, "INTEGER"},
        {QMetaType::Int, "INTEGER"},
        {QMetaType::UInt, "INTEGER"},
        {QMetaType::Long, "INTEGER"},
        {QMetaType::ULong, "INTEGER"},
        {QMetaType::LongLong, "INTEGER"},
        {QMetaType::ULongLong, "INTEGER"},
        {QMetaType::Double, "DOUBLE"},
        {QMetaType::Float, "FLOAT"},

        {QVariant::String, "VARCHAR"},

        {QVariant::Bool, "BOOL"},

        {QVariant::Date, "DATE"},
        {QVariant::Time, "TIME"},
        {QVariant::DateTime, "DATETIME"}
    };
    if(!map.contains(typeId)){
        QString info = QString("Type is not supported. Type:").append(QVariant::typeToName(typeId));
        qFatal(info.toUtf8());
    }
    return map[typeId];
}

QString IOrmSqliteDialect::getLimitString(int count)
{
    return QString("LIMIT ").append(QString::number(count));
}

QString IOrmSqliteDialect::getLimitString(quint64 start, quint64 count)
{
    return QString("LIMIT ").append(QString::number(count)).append(" OFFSET ").append(QString::number(start));
}


QVariant IOrmSqliteDialect::getInsertedPrimaryKey(QSqlDatabase& db, IOrmTableWare &table, const QVariant& rowid)
{
    const auto& info = table.getOrmEntityInfo();
    ISqlQuery query(db);
    QString sql = "select " + info->primaryKey + " from " + info->entityName
            + " where rowid = :rowid";
    query.prepare(sql);
    query.bindValue(":rowid", rowid);
    query.exec();
    return IOrmUtil::getVariant(query);
}

bool IOrmSqliteDialect::truncateTable(QSqlDatabase &db, const IOrmTableInfo &info)
{
    Q_UNUSED(db)
    Q_UNUSED(info)
    qFatal("sqlite do not support truncate, please use clearTable function");
    return false;
}

$PackageWebCoreEnd
