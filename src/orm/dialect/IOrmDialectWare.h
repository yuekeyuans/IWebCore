#pragma once

#include "base/IHeaderUtil.h"
#include "orm/IOrmUtil.h"
#include "orm/clause/IOrmCondition.h"
#include "orm/ISqlQuery.h"

$PackageWebCoreBegin

class IOrmTableInfo;
class IOrmEntityWare;
class IOrmEntityInfoWare;
class IOrmTableWare;
class IOrmViewWare;

class IOrmDialectWare
{
    $AsWare
public:
    IOrmDialectWare() = default;
    virtual ~IOrmDialectWare() = default;

    virtual bool exec(QSqlDatabase& db, const QString& sql);

    virtual bool insert(QSqlDatabase& db, IOrmTableWare& table, const QStringList& columns);

    virtual bool update(QSqlDatabase& db, const IOrmTableWare& table);
    virtual bool update(QSqlDatabase& db, const IOrmTableWare& table, const QStringList& columns);
    virtual bool update(QSqlDatabase& db, const IOrmTableInfo& info, const QMap<QString, QVariant> &map, const IOrmCondition &condition);

    virtual bool deleted(QSqlDatabase& db, const IOrmTableWare& interface);
    virtual bool deleted(QSqlDatabase& db, const IOrmTableInfo& info, const IOrmCondition& condition);
    virtual bool deleteByPrimaryKey(QSqlDatabase& db, const IOrmTableInfo& info, const QVariant& key);

    template<class T>
    T findOne(QSqlDatabase& db, const IOrmCondition& condition);
    virtual bool findOne(ISqlQuery& db, const IOrmEntityInfoWare& info, const IOrmCondition& condition);

    template<class T>
    T findOneByPrimaryKey(QSqlDatabase& db, const QVariant& key);
    virtual bool findOneByPrimaryKey(ISqlQuery& query, const IOrmTableInfo& info, const QVariant& key);

    template<class T>
    QList<T> findAll(QSqlDatabase& db);
    virtual bool findAll(ISqlQuery& query, const IOrmEntityInfoWare& info);

    template<class T>
    QList<T> findAll(QSqlDatabase& db, const IOrmCondition& condition);
    virtual bool findAll(ISqlQuery& query, const IOrmEntityInfoWare& info, const IOrmCondition& condition);
    virtual QList<QMap<QString, QVariant>> findColumns(QSqlDatabase& db, const IOrmEntityInfoWare& info, const QStringList& columns);
    virtual QList<QMap<QString, QVariant>> findColumns(QSqlDatabase& db, const IOrmEntityInfoWare& info, const QStringList& columns, const IOrmCondition& condition);

    virtual size_t count(QSqlDatabase& db, const IOrmEntityInfoWare& info);
    virtual size_t count(QSqlDatabase& db, const IOrmEntityInfoWare& info, const IOrmCondition& condition);

    virtual bool clearTable(QSqlDatabase& db, const IOrmTableInfo& info);
    virtual bool truncateTable(QSqlDatabase& db, const IOrmTableInfo& info);

    virtual QString dialectType() = 0;
    virtual QString createTableSqlClause(const IOrmTableInfo& table);

    virtual QString getSqlType(const int typeId) = 0;
    virtual QString getLimitString(int count) = 0;
    virtual QString getLimitString(quint64 start, quint64 count) = 0;

    // 对于 bind 的数据需要装饰
    virtual QVariant decorateValue(const IOrmTableInfo& info, const QString& name, const QVariant& value);  

    // 插入语句
    virtual QString getUpdateSqlClause(const IOrmTableInfo& info, const QStringList& columns);
    virtual QString getInsertSqlClause(const IOrmTableInfo& info, const QStringList& columns);

    virtual QString createSqlCommonKeyClause(const IOrmTableInfo& table, const QString& name);
};

template<class T>
T IOrmDialectWare::findOne(QSqlDatabase& db, const IOrmCondition &condition)
{
    ISqlQuery query(db);
    auto result = findOne(query, T::entityInfo(), condition);
    if(!result){
        return {};
    }
    return IOrmUtil::getBean<T>(query);
}

template<class T>
T IOrmDialectWare::findOneByPrimaryKey(QSqlDatabase &db, const QVariant &key)
{
    ISqlQuery query(db);
    auto result = findOneByPrimaryKey(query, T::entityInfo(), key);
    if(!result){
        return {};
    }
    return IOrmUtil::getBean<T>(query);
}

template<class T>
QList<T> IOrmDialectWare::findAll(QSqlDatabase &db)
{
    ISqlQuery query(db);
    auto result = findAll(query, T::entityInfo());
    if(!result){
        return {};
    }
    return IOrmUtil::getBeans<T>(query);
}

template<class T>
QList<T> IOrmDialectWare::findAll(QSqlDatabase &db, const IOrmCondition &condition)
{
    ISqlQuery query(db);
    auto result = findAll(query, T::entityInfo(), condition);
    if(!result){
        return {};
    }
    return IOrmUtil::getBeans<T>(query);
}

$PackageWebCoreEnd
