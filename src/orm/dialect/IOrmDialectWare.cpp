#include "IOrmDialectWare.h"
#include "core/base/IMetaUtil.h"
#include "core/base/IConstantUtil.h"
#include "orm/IOrmUtil.h"
#include "orm/IOrmManage.h"
#include "orm/ISqlQuery.h"

#include "orm/tableview/IOrmEntityWare.h"
#include "orm/tableview/IOrmTableWare.h"
#include "orm/tableview/IOrmViewWare.h"

#include "orm/tableview/IOrmEntityInfoWare.h"
#include "orm/tableview/IOrmTableInfo.h"
#include "orm/tableview/IOrmViewInfo.h"

#include "orm/clause/IOrmCondition.h"

$PackageWebCoreBegin

bool IOrmDialectWare::exec(QSqlDatabase &db, const QString &sql)
{
    ISqlQuery query(db);
    return query.exec(sql);
}

bool IOrmDialectWare::insert(QSqlDatabase& db, IOrmTableWare& table, const QStringList &columns)
{
    const auto info = table.getOrmEntityInfo();
    auto sql = getInsertSqlClause(*info, columns);

    ISqlQuery query(db);
    query.prepare(sql);
    for(const auto& col : columns){
        auto originVale = table.getFieldValue(col);
        auto decoratedValue = decorateValue(*info, col, originVale);
        query.bindValue(":" + col, decoratedValue);

        if(col == info->autoGenerateKey && info->getFieldTypeId(col) == QMetaType::QString){
            table.setFieldValue(col, decoratedValue);
        }
    }
    auto result = query.exec();
    if(!result){
        return result;
    }

    // NOTE: here is different via orm framework.
    if(!info->autoGenerateKey.isEmpty()){
        auto key = info->getFieldTypeId(info->autoGenerateKey);
        if(IToeUtil::isPrimaryKeyType(key)){
            table.setFieldValue(info->autoGenerateKey, query.lastInsertId());
        }
    }

    return result;
}

bool IOrmDialectWare::update(QSqlDatabase &db, const IOrmTableWare &table)
{
    const auto& info = table.getOrmEntityInfo();
    QStringList columns = info->fieldNames;
    columns.removeOne(info->primaryKey);
    auto sql = getUpdateSqlClause(*info, columns);

    ISqlQuery query(db);
    query.prepare(sql);
    for(const auto& field : info->fieldNames){
        query.bindValue(":" + field, table.getFieldValue(field));
    }
    return query.exec();
}

bool IOrmDialectWare::update(QSqlDatabase &db, const IOrmTableWare &table, const QStringList &columns)
{
    if(columns.isEmpty()){
        return false;
    }
    const auto& info = table.getOrmEntityInfo();
    const auto& pk = info->primaryKey;
    if(columns.contains(pk)){
        qFatal("error, update`s columns can`t contains primary key field");
    }

    auto sql = getUpdateSqlClause(*info, columns);

    ISqlQuery query(db);
    query.prepare(sql);
    for(const auto& field : columns){
        query.bindValue(":" + field, table.getFieldValue(field));
    }
    query.bindValue(":" + pk, table.getFieldValue(pk));
    return query.exec();
}

bool IOrmDialectWare::update(QSqlDatabase &db, const IOrmTableInfo &info, const QMap<QString, QVariant> &map, const IOrmCondition &condition)
{
    if(map.isEmpty()){
        return false;
    }
    if(!condition.isValid()){
        qFatal("condition must not be invalid");
    }

    ISqlQuery query(db);
    QString sql = QString("UPDATE ").append(info.entityName).append(" SET ");
    QStringList args;
    const auto& keys = map.keys();
    for(const auto key : keys){
        QString placer = QString(':').append(key);
        args.append(QString(key).append(" = ").append(placer));
        query.binParameter(placer, map[key]);
    }
    sql.append(args.join(", "));
    sql.append(' ').append(condition.toSql());
    condition.bindParameters(query);

    query.prepare(sql);
    return query.exec();
}

bool IOrmDialectWare::deleted(QSqlDatabase &db, const IOrmTableWare &ware)
{
    const auto& info = ware.getOrmEntityInfo();
    const auto& pk = info->primaryKey;
    QString sql = QString("DELETE FROM ").append(info->entityName).append(" WHERE ").append(pk)
            .append(" = :").append(pk);
    ISqlQuery query(db);
    query.prepare(sql);
    query.bindValue(":" + pk, ware.getFieldValue(pk));
    return query.exec();
}

bool IOrmDialectWare::deleted(QSqlDatabase& db, const IOrmTableInfo& info, const IOrmCondition& condition)
{
    QString sql = "DELETE FROM " + info.entityName;
    auto whereCondition = condition.toSql();
    if(!whereCondition.isEmpty()){
        sql.append(' ').append(whereCondition);
    }
    ISqlQuery query(db);
    query.prepare(sql);
    condition.bindParameters(query);
    return query.exec();
}

bool IOrmDialectWare::deleteByPrimaryKey(QSqlDatabase& db, const IOrmTableInfo &info, const QVariant &key)
{
    QString sql = QString("DELETE FROM ") + info.entityName + " WHERE ";
    sql.append(info.primaryKey).append(" = :").append(info.primaryKey);
    ISqlQuery query(db);
    query.prepare(sql);
    query.bindValue(":" + info.primaryKey, key);
    return query.exec();
}

bool IOrmDialectWare::findOne(ISqlQuery &query, const IOrmEntityInfoWare &info, const IOrmCondition &condition)
{
    QString sql = "SELECT * FROM " + info.entityName;
    auto where = condition.toSql();
    if(!where.isEmpty()){
        sql.append(' ').append(where);
    }
    query.prepare(sql);
    condition.bindParameters(query);
    return query.exec();
}

bool IOrmDialectWare::findOneByPrimaryKey(ISqlQuery &query, const IOrmTableInfo &info, const QVariant &key)
{
    const auto& pk = info.primaryKey;
    QString sql = "SELECT * FROM " + info.entityName;
    sql.append(" WHERE ").append(pk).append(" = :").append(pk);
    query.prepare(sql);
    query.bindValue(":"+ pk, key);
    return query.exec();
}

bool IOrmDialectWare::findAll(ISqlQuery &query, const IOrmEntityInfoWare &info)
{
    QString sql = "SELECT * FROM " + info.entityName;
    return query.exec(sql);
}

bool IOrmDialectWare::findAll(ISqlQuery &query, const IOrmEntityInfoWare &info, const IOrmCondition &condition)
{
    QString sql = "SELECT * FROM " + info.entityName;
    QString where = condition.toSql();
    if(!where.isEmpty()){
        sql.append(' ').append(where);
    }
    query.prepare(sql);
    condition.bindParameters(query);
    return query.exec();
}

QList<QMap<QString, QVariant> > IOrmDialectWare::findColumns(QSqlDatabase &db, const IOrmEntityInfoWare &info, const QStringList &columns)
{
    QString sql = "SELECT ";
    sql.append(columns.join(", ")).append(" FROM ").append(info.entityName);
    ISqlQuery query(db);
    auto result = query.exec(sql);
    if(!result){
        return {};
    }
    return IOrmUtil::getMapList(query);
}

QList<QMap<QString, QVariant> > IOrmDialectWare::findColumns(QSqlDatabase &db, const IOrmEntityInfoWare &info, const QStringList &columns, const IOrmCondition &condition)
{
    QString sql = "SELECT ";
    sql.append(columns.join(", ")).append(" FROM ").append(info.entityName);
    if(condition.isValid()){
        sql.append(' ').append(condition.toSql());
    }
    ISqlQuery query(db);
    query.prepare(sql);
    condition.bindParameters(query);
    auto result = query.exec();
    if(!result){
        return {};
    }
    return IOrmUtil::getMapList(query);
}

size_t IOrmDialectWare::count(QSqlDatabase &db, const IOrmEntityInfoWare &info)
{
    QString sql = QString("SELECT COUNT(1) FROM ") + info.entityName;
    ISqlQuery query(db);
    auto result = query.exec(sql);
    if(!result){
        qFatal("error");
        return -1;
    }

    bool ok;
    auto ret = IOrmUtil::getLongLong(query, ok);
    if(!ok){
        qFatal("error");
        return -1;
    }
    return ret;
}

size_t IOrmDialectWare::count(QSqlDatabase &db, const IOrmEntityInfoWare &info, const IOrmCondition &condition)
{
    Q_UNUSED(condition)
    QString sql = QString("SELECT COUNT(1) FROM ") + info.entityName;

    auto where = condition.toSql();
    if(!where.isEmpty()){
        sql.append(' ').append(where);
    }

    ISqlQuery query(db);
    query.prepare(sql);
    condition.bindParameters(query);
    query.exec();

    bool ok;
    auto ret = IOrmUtil::getLongLong(query, ok);
    if(!ok){
        return -1;
    }
    return ret;
}

bool IOrmDialectWare::clearTable(QSqlDatabase &db, const IOrmTableInfo &info)
{
    QString sql = "DELETE FROM " + info.entityName;
    ISqlQuery query(db);
    return query.exec(sql);
}

QString IOrmDialectWare::createTableSqlClause(const IOrmTableInfo& info)
{
    QString sql = QString("CREATE TABLE IF NOT EXISTS ").append(info.entityName);

    QStringList fields;
    for (const auto &name : info.fieldNames) {
        fields.append(createSqlCommonKeyClause(info,name));
    }
    sql.append(" (").append(fields.join(", ") + ')');
    return sql;
}

// 1 处理空数据
// 2 处理 primary key
QVariant IOrmDialectWare::decorateValue(const IOrmTableInfo &info, const QString& name, const QVariant &value){
    // deal with primary key
    if( name == info.autoGenerateKey){
        auto valueType = value.type();
        if(valueType == QVariant::String){
            auto typeId = info.getFieldTypeId(name);
            return IOrmManage::autoGeneratFieldValue(typeId, info.autoGenerateType);
        }

        if(IToeUtil::isPrimaryKeyType(QMetaType::Type(valueType))){  // ignore autoGenerateType
            return {};
        }
    }
    if(value.isNull()
            || !value.isValid()
            || (value.type() == QVariant::String && value.toString().isEmpty())){
        return {};
    }

    return value;
}

QString IOrmDialectWare::getUpdateSqlClause(const IOrmTableInfo &info, const QStringList &columns)
{
    QString sql = QString("UPDATE ").append(info.entityName).append(" SET ");
    QStringList args;
    for(const auto& fd : columns){
        QString piece = fd + " = :" + fd;
        args.append(piece);
    }
    sql.append(args.join(", "));

    const QString& pk = info.primaryKey;
    sql.append(" WHERE ").append(pk).append(" = :").append(pk);
    return sql;
}

QString IOrmDialectWare::getInsertSqlClause(const IOrmTableInfo& info, const QStringList &columns)
{
    QString sql = "insert into ";
    sql.append(info.entityName);

    QStringList keys;
    QStringList values;

    auto names = info.fieldNames;
    for(const auto& fd : columns){
        keys.append(fd);
        values.append(":" + fd);
    }
    sql.append(" ( " + keys.join(", ") + " ) ");
    sql.append(" values ( " + values.join(", ") + " ) ");
    return sql;
}

bool IOrmDialectWare::truncateTable(QSqlDatabase &db, const IOrmTableInfo &info)
{
    QString sql = "TRUNCATE TABLE " + info.entityName;
    ISqlQuery query(db);
    return query.exec(sql);
}

QString IOrmDialectWare::createSqlCommonKeyClause(const IOrmTableInfo& info, const QString &name)
{
    auto typeId = info.fieldTypeIds[info.fieldNames.indexOf(name)];
    auto sqlType = info.getFieldSqlType(name);  // sql type
    if(sqlType.isEmpty()){
        sqlType = getSqlType(typeId);
    }

    QString piece = name + " " + sqlType;

    if(info.notNullNKeys.contains(name)){
        piece.append(" NOT NULL");
    }

    if(info.uniqueKeys.contains(name)){
        piece.append(" UNIQUE");
    }

    if(info.primaryKey == name){
        piece.append(" PRIMARY KEY");
    }

    if(info.autoGenerateKey == name && info.autoGenerateType == "default"){
        auto typeId = info.getFieldTypeId(name);
        if(typeId != QMetaType::QString && IToeUtil::isPrimaryKeyType(typeId)){
            piece.append(" AUTOINCREMENT");
        }
    }
    return piece;
}


$PackageWebCoreEnd
