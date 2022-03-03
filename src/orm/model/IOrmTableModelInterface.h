#pragma once

#include "base/IHeaderUtil.h"
#include "base/IConstantUtil.h"
#include "orm/IOrmManage.h"
#include "orm/ISqlQuery.h"
#include "orm/tableview/IOrmEntityWare.h"
#include "orm/tableview/IOrmTableInfo.h"
#include "orm/dialect/IOrmDialectWare.h"
#include "orm/clause/IOrmQueryClause.h"
#include "orm/clause/IOrmCondition.h"

$PackageWebCoreBegin

/*!
 * NOTE: 这里的 db 需要特殊声明, 参考 非类型模板参数, 字符串。
 */

extern const char DefaultDatabaseName[];

template<typename T, const char * dbConnectionName = DefaultDatabaseName>
class IOrmTableModelInterface
{
public:
    IOrmTableModelInterface() = default;
    virtual ~IOrmTableModelInterface() = default;

    // common exec
    bool exec(const QString& sql);
    ISqlQuery execedQuery(const QString& sql);

    // insert
    bool insert(const QString& sql);
    bool insert(T& table, const QStringList& columns = {});
    bool insert(QList<T>& tables, const QStringList& columns = {});

    // update
    bool update(const T& table);
    bool update(const QList<T>& tables);
    bool update(const T& table, const QStringList& columns);
    bool update(const QList<T>& tables, const QStringList& columns);
    bool update(const QMap<QString, QVariant>& map, const IOrmCondition& condition);

    // delete
    bool deleted(T& table);
    bool deleted(const QString& sql);   // 直接使用 sql
    bool deleted(QList<T>& tables);
    bool deleted(const IOrmCondition& condition);
    bool deleteByPrimaryKey(const QVariant& variant);

    // find
    T findOne(const IOrmCondition& condition);
    T findOneByPriamaryKey(const QVariant& variant);
    QList<T> findAll();
    QList<T> findAll(const IOrmCondition& condition);
    QList<QMap<QString, QVariant>> findColumns(const IOrmCondition& condition); // columns is all
    QList<QMap<QString, QVariant>> findColumns(const QStringList& columns);
    QList<QMap<QString, QVariant>> findColumns(const QStringList& columns, const IOrmCondition& condition);

    // others
    size_t count();
    size_t count(const IOrmCondition& condition);
    bool clearTable();
    bool truncateTable();

    T toObject(const QMap<QString, QVariant>& map);
    T toObject(const QJsonObject& obj);

    QSqlDatabase& getDatabase();
    IOrmDialectWare* getDialect();
    ISqlQuery getQuery();

protected:
    const QString connectionName {dbConnectionName};
};

template<typename T, const char* dbConnectionName>
bool IOrmTableModelInterface<T, dbConnectionName>::exec(const QString &sql)
{
    auto dialect = getDialect();
    auto db = getDatabase();
    return dialect->exec(db, sql);
}


template<typename T, const char* dbConnectionName>
ISqlQuery IOrmTableModelInterface<T, dbConnectionName>::execedQuery(const QString &sql)
{
    ISqlQuery query = getQuery();
    query.exec(sql);
    return query;
}


template<typename T, const char* dbConnectionName>
bool IOrmTableModelInterface<T, dbConnectionName>::insert(const QString &sql)
{
    return exec(sql);
}


template<typename T, const char* dbConnectionName>
bool IOrmTableModelInterface<T, dbConnectionName>::insert(T &table, const QStringList& columns)
{
    auto dialect = getDialect();
    const auto& cols = columns.isEmpty() ?  T::tableInfo().fieldNames : columns;
    auto db = getDatabase();
    return dialect->insert(db, table, cols);
}

template<typename T, const char* dbConnectionName>
bool IOrmTableModelInterface<T, dbConnectionName>::insert(QList<T>& tables, const QStringList &columns)
{
    if(tables.isEmpty()){
        return true;
    }

    IOrmDialectWare* dialect = getDialect();
    QSqlDatabase& db = getDatabase();
    const auto& cols = columns.isEmpty() ?  T::tableInfo().fieldNames : columns;

    db.transaction();
    for(auto& table : tables){
        dialect->insert(db, table, cols);
    }
    return db.commit();
}

// TODO: 感觉这个不应该在这里实现，而应该分离在dialect 当中实现。
template<typename T, const char* dbConnectionName>
bool IOrmTableModelInterface<T, dbConnectionName>::update(const QList<T> &tables)
{
    IOrmDialectWare* dialect = getDialect();
    QSqlDatabase& db = getDatabase();
    db.transaction();
    for(const auto table : tables){
        dialect->update(db, table);
    }
    return db.commit();
}

template<typename T, const char* dbConnectionName>
bool IOrmTableModelInterface<T, dbConnectionName>::update(const T &table)
{
    IOrmDialectWare* dialect = getDialect();
    QSqlDatabase& db = getDatabase();
    return dialect->update(db, table);
}

template<typename T, const char* dbConnectionName>
bool IOrmTableModelInterface<T, dbConnectionName>::update(const T &table, const QStringList &columns)
{
    IOrmDialectWare* dialect = getDialect();
    QSqlDatabase& db = getDatabase();
    return dialect->update(db, table, columns);
}


template<typename T, const char* dbConnectionName>
bool IOrmTableModelInterface<T, dbConnectionName>::update(const QList<T> &tables, const QStringList &columns)
{
    IOrmDialectWare* dialect = getDialect();
    QSqlDatabase& db = getDatabase();
    db.transaction();
    for(const auto table : tables){
        dialect->update(db, table, columns);
    }
    return db.commit();
}


template<typename T, const char* dbConnectionName>
bool IOrmTableModelInterface<T, dbConnectionName>::update(const QMap<QString, QVariant> &map, const IOrmCondition &condition)
{
    IOrmDialectWare* dialect = getDialect();
    QSqlDatabase& db = getDatabase();
    return dialect->update(db, T::tableInfo(), map, condition);
}


template<typename T, const char* dbConnectionName>
bool IOrmTableModelInterface<T, dbConnectionName>::deleted(T &t){
    IOrmDialectWare* dialect = getDialect();
    QSqlDatabase& db = getDatabase();
    return dialect->deleted(db, t);
}


template<typename T, const char* dbConnectionName>
bool IOrmTableModelInterface<T, dbConnectionName>::deleted(const QString &sql)
{
    return exec(sql);
}


template<typename T, const char* dbConnectionName>
bool IOrmTableModelInterface<T, dbConnectionName>::deleted(QList<T> &tables)
{
    if(tables.length() == 0){
        return true;
    }

    const IOrmTableInfo& info = T::tableInfo();
    const auto& pk = info.primaryKey;
    IOrmDialectWare* dialect = getDialect();
    QSqlDatabase& db = getDatabase();

    QList<QVariant> args;
    for(const IOrmEntityWare& table : tables){
        args << table.getFieldValue(pk);
    }
    IOrmCondition condition;
    condition.whereIn(info.primaryKey, args);
    return dialect->deleted(db, info, condition);
}


template<typename T, const char* dbConnectionName>
bool IOrmTableModelInterface<T, dbConnectionName>::deleted(const IOrmCondition &condition)
{
    auto dialect = getDialect();
    QSqlDatabase& db = getDatabase();
    return dialect->deleted(db, T::tableInfo(), condition);
}


template<typename T, const char* dbConnectionName>
bool IOrmTableModelInterface<T, dbConnectionName>::deleteByPrimaryKey(const QVariant &variant)
{
    IOrmDialectWare* dialect = getDialect();
    QSqlDatabase& db = getDatabase();
    return dialect->deleteByPrimaryKey(db, T::tableInfo(), variant);
}


template<typename T, const char* dbConnectionName>
T IOrmTableModelInterface<T, dbConnectionName>::findOne(const IOrmCondition &condition)
{
    IOrmDialectWare* dialect = getDialect();
    QSqlDatabase& db = getDatabase();
    return dialect->findOne<T>(db, condition);
}

// TODO: 这里的 key也可以改为 模板的。

template<typename T, const char* dbConnectionName>
T IOrmTableModelInterface<T, dbConnectionName>::findOneByPriamaryKey(const QVariant &key)
{
    IOrmDialectWare* dialect = getDialect();
    QSqlDatabase& db = getDatabase();
    return dialect->findOneByPrimaryKey<T>(db, key);
}


template<typename T, const char* dbConnectionName>
QList<T> IOrmTableModelInterface<T, dbConnectionName>::findAll()
{
    IOrmDialectWare* dialect = getDialect();
    QSqlDatabase& db = getDatabase();
    return dialect->findAll<T>(db);
}


template<typename T, const char* dbConnectionName>
QList<T> IOrmTableModelInterface<T, dbConnectionName>::findAll(const IOrmCondition &condition)
{
    IOrmDialectWare* dialect = getDialect();
    QSqlDatabase& db = getDatabase();
    return dialect->findAll<T>(db, condition);
}


template<typename T, const char* dbConnectionName>
QList<QMap<QString, QVariant>> IOrmTableModelInterface<T, dbConnectionName>::findColumns(const IOrmCondition &condition)
{
    IOrmDialectWare* dialect = getDialect();
    QSqlDatabase& db = getDatabase();
    return dialect->findColumns(db, T::tableInfo(), condition);
}


template<typename T, const char* dbConnectionName>
QList<QMap<QString, QVariant>> IOrmTableModelInterface<T, dbConnectionName>::findColumns(const QStringList &columns)
{
    IOrmDialectWare* dialect = getDialect();
    QSqlDatabase& db = getDatabase();
    return dialect->findColumns(db, T::tableInfo(), columns);
}


template<typename T, const char* dbConnectionName>
QList<QMap<QString, QVariant>> IOrmTableModelInterface<T, dbConnectionName>::findColumns(const QStringList &columns, const IOrmCondition &condition)
{
    IOrmDialectWare* dialect = getDialect();
    QSqlDatabase& db = getDatabase();
    return dialect->findColumns(db, T::tableInfo(), columns, condition);
}


template<typename T, const char* dbConnectionName>
size_t IOrmTableModelInterface<T, dbConnectionName>::count()
{
    IOrmDialectWare* dialect = getDialect();
    QSqlDatabase& db = getDatabase();
    return dialect->count(db, T::tableInfo());
}


template<typename T, const char* dbConnectionName>
size_t IOrmTableModelInterface<T, dbConnectionName>::count(const IOrmCondition &condition)
{
    IOrmDialectWare* dialect = getDialect();
    QSqlDatabase& db = getDatabase();
    return dialect->count(db, T::tableInfo(), condition);
}


template<typename T, const char* dbConnectionName>
bool IOrmTableModelInterface<T, dbConnectionName>::clearTable()
{
    IOrmDialectWare* dialect = getDialect();
    QSqlDatabase& db = getDatabase();
    return dialect->clearTable(db, T::tableInfo());
}


template<typename T, const char* dbConnectionName>
bool IOrmTableModelInterface<T, dbConnectionName>::truncateTable()
{
    IOrmDialectWare* dialect = getDialect();
    QSqlDatabase& db = getDatabase();
    return dialect->truncateTable(db, T::tableInfo());
}


template<typename T, const char* dbConnectionName>
T IOrmTableModelInterface<T, dbConnectionName>::toObject(const QMap<QString, QVariant> &map)
{
    return T::toObject(map);
}


template<typename T, const char* dbConnectionName>
T IOrmTableModelInterface<T, dbConnectionName>::toObject(const QJsonObject &obj)
{
    return T::toObject(obj);
}

template<typename T, const char* dbConnectionName>
IOrmDialectWare *IOrmTableModelInterface<T, dbConnectionName>::getDialect(){
    const QSqlDatabase& db = getDatabase();
    auto name = db.driverName();
    return IOrmManage::getDialect(name);
}


template<typename T, const char* dbConnectionName>
ISqlQuery IOrmTableModelInterface<T, dbConnectionName>::getQuery(){
    const QSqlDatabase& db = getDatabase();
    return ISqlQuery(db);
}


template<typename T, const char* dbConnectionName>
QSqlDatabase &IOrmTableModelInterface<T, dbConnectionName>::getDatabase(){
    return IOrmManage::getDataBase(dbConnectionName);
}

$PackageWebCoreEnd
