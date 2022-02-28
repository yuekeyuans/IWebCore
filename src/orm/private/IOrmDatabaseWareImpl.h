#pragma once

#include "base/IHeaderUtil.h"
#include "orm/database/IOrmDataSource.h"

$PackageWebCoreBegin

class IOrmDatabaseWareImpl{
public:
    IOrmDatabaseWareImpl() = default;

    bool openDatabase(IOrmDataSource& datasource);
    void closeDatabase();
    void registerTable(const IOrmTableInfo& info, const QString& sql);
    void execSql(const QString& sql);
    void checkTableInfo(const IOrmTableInfo& info);
public:
    QSqlDatabase m_db;
    IOrmDataSource m_dataSource;
    QStringList m_existedTables;
    QStringList m_existedViews;
    QStringList m_tables;       // this table is user registered tables
    QStringList m_views;        // this is view defined in database
};

$PackageWebCoreEnd
