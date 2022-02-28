#pragma once

#include <IWebCore>

extern const char MySqlWorldConnectionName[];

class MySqlWorldDatabase : public IOrmDatabaseInterface<MySqlWorldDatabase>
{
    Q_GADGET
    $AsDatabase(MySqlWorldDatabase)
public:
    MySqlWorldDatabase();

public:
    virtual IOrmDataSource configDataSource() final;
    virtual void registerTables() final;
};

