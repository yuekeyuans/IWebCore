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
public:
    IOrmEntityModelWare() = default;

    size_t count();
    size_t count(const IOrmCondition& condition);

    QSqlDatabase& getDatabase();
    IOrmDialectWare* getDialect();
    ISqlQuery getQuery();
};


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
