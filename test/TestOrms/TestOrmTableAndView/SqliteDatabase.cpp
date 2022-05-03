#include "SqliteDatabase.h"

#include "TableBean.h"

#include "ViewBean.h"

SqliteDatabase::SqliteDatabase()
{
}

IOrmDataSource SqliteDatabase::configDataSource()
{
    IOrmDataSource source;
    source.driverName = "QSQLITE";
    source.databaseName = "jjjjj.db";
    return source;
}

void SqliteDatabase::registerEntities()
{
    registerTable<TableBean>();
    registerView<ViewBean>("create view ViewBean as select id from TableBean");
}
