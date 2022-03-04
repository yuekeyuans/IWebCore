#pragma once

#include "base/IHeaderUtil.h"
#include "orm/dialect/IOrmDialectWare.h"
#include "orm/ISqlQuery.h"
#include "orm/IOrmManage.h"

$PackageWebCoreBegin

extern const char DefaultDatabaseName[];

template<typename T, const char * dbConnectionName = DefaultDatabaseName>
class IOrmEntityModelWare
{
    $AsWare
public:
    IOrmEntityModelWare() = default;

    bool exec(const QString& sql);
    ISqlQuery execedQuery(const QString& sql);

    T findOne(const IOrmCondition& condition);
    QList<T> findAll();
    QList<T> findAll(const IOrmCondition& condition);
    QList<QMap<QString, QVariant>> findColumns(const IOrmCondition& condition); // columns is all
    QList<QMap<QString, QVariant>> findColumns(const QStringList& columns);
    QList<QMap<QString, QVariant>> findColumns(const QStringList& columns, const IOrmCondition& condition);

    size_t count();
    size_t count(const IOrmCondition& condition);

    T toObject(const QMap<QString, QVariant>& map);
    T toObject(const QJsonObject& obj);

    QSqlDatabase& getDatabase();
    IOrmDialectWare* getDialect();
    ISqlQuery getQuery();
};

template<typename T, const char* dbConnectionName>
bool IOrmEntityModelWare<T, dbConnectionName>::exec(const QString &sql)
{
    auto dialect = getDialect();
    auto db = getDatabase();
    return dialect->exec(db, sql);
}

template<typename T, const char* dbConnectionName>
ISqlQuery IOrmEntityModelWare<T, dbConnectionName>::execedQuery(const QString &sql)
{
    ISqlQuery query = getQuery();
    query.exec(sql);
    return query;
}

template<typename T, const char* dbConnectionName>
T IOrmEntityModelWare<T, dbConnectionName>::findOne(const IOrmCondition &condition)
{
    IOrmDialectWare* dialect = getDialect();
    QSqlDatabase& db = getDatabase();
    return dialect->findOne<T>(db, condition);
}

template<typename T, const char* dbConnectionName>
QList<T> IOrmEntityModelWare<T, dbConnectionName>::findAll()
{
    IOrmDialectWare* dialect = getDialect();
    QSqlDatabase& db = getDatabase();
    return dialect->findAll<T>(db);
}

template<typename T, const char* dbConnectionName>
QList<T> IOrmEntityModelWare<T, dbConnectionName>::findAll(const IOrmCondition &condition)
{
    IOrmDialectWare* dialect = getDialect();
    QSqlDatabase& db = getDatabase();
    return dialect->findAll<T>(db, condition);
}

template<typename T, const char* dbConnectionName>
QList<QMap<QString, QVariant>> IOrmEntityModelWare<T, dbConnectionName>::findColumns(const IOrmCondition &condition)
{
    IOrmDialectWare* dialect = getDialect();
    QSqlDatabase& db = getDatabase();
    return dialect->findColumns(db, T::entityInfo(), condition);
}

template<typename T, const char* dbConnectionName>
QList<QMap<QString, QVariant>> IOrmEntityModelWare<T, dbConnectionName>::findColumns(const QStringList &columns)
{
    IOrmDialectWare* dialect = getDialect();
    QSqlDatabase& db = getDatabase();
    return dialect->findColumns(db, T::entityInfo(), columns);
}

template<typename T, const char* dbConnectionName>
QList<QMap<QString, QVariant>> IOrmEntityModelWare<T, dbConnectionName>::findColumns(const QStringList &columns, const IOrmCondition &condition)
{
    IOrmDialectWare* dialect = getDialect();
    QSqlDatabase& db = getDatabase();
    return dialect->findColumns(db, T::entityInfo(), columns, condition);
}

template<typename T, const char* dbConnectionName>
size_t IOrmEntityModelWare<T, dbConnectionName>::count()
{
    IOrmDialectWare* dialect = getDialect();
    QSqlDatabase& db = getDatabase();
    return dialect->count(db, T::entityInfo());
}

template<typename T, const char* dbConnectionName>
size_t IOrmEntityModelWare<T, dbConnectionName>::count(const IOrmCondition &condition)
{
    IOrmDialectWare* dialect = getDialect();
    QSqlDatabase& db = getDatabase();
    return dialect->count(db, T::entityInfo(), condition);
}

template<typename T, const char* dbConnectionName>
T IOrmEntityModelWare<T, dbConnectionName>::toObject(const QMap<QString, QVariant> &map)
{
    return T::toObject(map);
}

template<typename T, const char* dbConnectionName>
T IOrmEntityModelWare<T, dbConnectionName>::toObject(const QJsonObject &obj)
{
    return T::toObject(obj);
}

template<typename T, const char* dbConnectionName>
IOrmDialectWare *IOrmEntityModelWare<T, dbConnectionName>::getDialect(){
    const QSqlDatabase& db = getDatabase();
    auto name = db.driverName();
    return IOrmManage::getDialect(name);
}

template<typename T, const char* dbConnectionName>
ISqlQuery IOrmEntityModelWare<T, dbConnectionName>::getQuery(){
    const QSqlDatabase& db = getDatabase();
    return ISqlQuery(db);
}

template<typename T, const char* dbConnectionName>
QSqlDatabase &IOrmEntityModelWare<T, dbConnectionName>::getDatabase(){
    return IOrmManage::getDataBase(dbConnectionName);
}

$PackageWebCoreEnd
