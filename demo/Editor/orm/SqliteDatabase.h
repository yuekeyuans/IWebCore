#pragma once

#include <IWebCore>

class SqliteDatabase : public IOrmDatabaseInterface
{
    $AsDatabase(SqliteDatabase)
public:
    SqliteDatabase();

    virtual IOrmDataSource configDataSource() final;
    virtual void registerTables() final;
    virtual QSqlDatabase createDataBase() final;


public:
    static void openDatabase(QString path);
    static void closeDatabase();


private:
    QString m_path;

};

