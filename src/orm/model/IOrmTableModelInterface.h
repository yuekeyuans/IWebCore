#pragma once

#include "base/IHeaderUtil.h"
#include "base/IConstantUtil.h"
#include "orm/IOrmManage.h"
#include "orm/ISqlQuery.h"
#include "orm/model/IOrmEntityModeWare.h"
#include "orm/tableview/IOrmEntityWare.h"
#include "orm/tableview/IOrmTableInfo.h"
#include "orm/dialect/IOrmDialectWare.h"
#include "orm/clause/IOrmQueryClause.h"
#include "orm/clause/IOrmCondition.h"

$PackageWebCoreBegin

// TODO: 这里的 IOrmEntityModelWare 和 IOrmEntityModelUnit 需要重新考量

template<typename T, const char * dbConnectionName = DefaultDatabaseName>
class IOrmTableModelInterface : public IOrmEntityModelWare<T, dbConnectionName>
{
public:
    using IOrmEntityModelWare<T, dbConnectionName>::exec;
    using IOrmEntityModelWare<T, dbConnectionName>::getDialect;
    using IOrmEntityModelWare<T, dbConnectionName>::getDatabase;

public:
    IOrmTableModelInterface() = default;
    virtual ~IOrmTableModelInterface() = default;

    bool insert(const QString& sql);
    bool insert(T& table, const QStringList& columns = {});
    bool insert(QList<T>& tables, const QStringList& columns = {});

    bool update(const T& table);
    bool update(const QList<T>& tables);
    bool update(const T& table, const QStringList& columns);
    bool update(const QList<T>& tables, const QStringList& columns);
    bool update(const QMap<QString, QVariant>& map, const IOrmCondition& condition);

    bool deleted(T& table);
    bool deleted(const QString& sql);   // 直接使用 sql
    bool deleted(QList<T>& tables);
    bool deleted(const IOrmCondition& condition);
    bool deleteByPrimaryKey(const QVariant& variant);

    T findOneByPriamaryKey(const QVariant& variant);

    bool clearTable();
    bool truncateTable();

protected:
    const QString connectionName {dbConnectionName};
};

template<typename T, const char* dbConnectionName>
bool IOrmTableModelInterface<T, dbConnectionName>::insert(const QString &sql)
{
    return exec(sql);
}

template<typename T, const char* dbConnectionName>
bool IOrmTableModelInterface<T, dbConnectionName>::insert(T &table, const QStringList& columns)
{
    auto dialect = getDialect();
    const auto& cols = columns.isEmpty() ?  T::entityInfo().fieldNames : columns;
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
    const auto& cols = columns.isEmpty() ?  T::entityInfo().fieldNames : columns;

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
    return dialect->update(db, T::entityInfo(), map, condition);
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

    const IOrmTableInfo& info = T::entityInfo();
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
    return dialect->deleted(db, T::entityInfo(), condition);
}

template<typename T, const char* dbConnectionName>
bool IOrmTableModelInterface<T, dbConnectionName>::deleteByPrimaryKey(const QVariant &variant)
{
    IOrmDialectWare* dialect = getDialect();
    QSqlDatabase& db = getDatabase();
    return dialect->deleteByPrimaryKey(db, T::entityInfo(), variant);
}

template<typename T, const char* dbConnectionName>
T IOrmTableModelInterface<T, dbConnectionName>::findOneByPriamaryKey(const QVariant &key)
{
    IOrmDialectWare* dialect = getDialect();
    QSqlDatabase& db = getDatabase();
    return dialect->findOneByPrimaryKey<T>(db, key);
}

template<typename T, const char* dbConnectionName>
bool IOrmTableModelInterface<T, dbConnectionName>::clearTable()
{
    IOrmDialectWare* dialect = getDialect();
    QSqlDatabase& db = getDatabase();
    return dialect->clearTable(db, T::entityInfo());
}

template<typename T, const char* dbConnectionName>
bool IOrmTableModelInterface<T, dbConnectionName>::truncateTable()
{
    IOrmDialectWare* dialect = getDialect();
    QSqlDatabase& db = getDatabase();
    return dialect->truncateTable(db, T::entityInfo());
}

$PackageWebCoreEnd
