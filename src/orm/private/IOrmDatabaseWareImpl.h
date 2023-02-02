#pragma once

#include "core/base/IHeaderUtil.h"
#include "orm/database/IOrmDataSource.h"

$PackageWebCoreBegin

class IOrmTableInfo;
class IOrmViewInfo;

class IOrmDatabaseWareImpl{
public:
    IOrmDatabaseWareImpl() = default;

    bool openDatabase(IOrmDataSource& datasource);
    void closeDatabase();

    void registerTable(const IOrmTableInfo& info, const QString& sql);
    void registerView(const IOrmViewInfo& info, const QString& sql);

    void execSql(const QString& sql);
    void checkTableInfo(const IOrmTableInfo& info);
    void checkViewInfo(const IOrmViewInfo& info);
public:
    QSqlDatabase m_db;
    IOrmDataSource m_dataSource;
    QStringList m_existedTables;
    QStringList m_existedViews;
    QStringList m_tables;       // this table is user registered tables
    QStringList m_views;        // this is view defined in database
};

$PackageWebCoreEnd
