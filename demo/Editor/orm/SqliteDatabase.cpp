#include "SqliteDatabase.h"
#include "orm/DictInfoTable.h"

SqliteDatabase::SqliteDatabase()
{
//    $ConstructDatabase(SqliteDatabase)
}

IOrmDataSource SqliteDatabase::configDataSource()
{
    IOrmDataSource source;
    source.driverName = "QSQLITE";
    source.connectionName = "default";
    source.databaseName = m_path;
    return source;
}

void SqliteDatabase::registerTables()
{
    registerTable<DictInfoTable>();
}

QSqlDatabase SqliteDatabase::createDataBase()
{
    auto dataSource = configDataSource();
    auto db = pimpl->createDatabase(dataSource);
    registerTables();
    return db;
}

void SqliteDatabase::openDatabase(QString path)
{
    closeDatabase();



    auto inst = instance();
    inst->m_path = path;
    inst->initDatabase();
    IOrmBase::registerDataBase(inst);
}

void SqliteDatabase::closeDatabase()
{
    auto inst = instance();
    inst->pimpl->closeDatabase();
    IOrmBase::unregisterDatabase(inst);
}
