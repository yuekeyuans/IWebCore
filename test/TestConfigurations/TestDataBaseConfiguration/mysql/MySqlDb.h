#pragma once

#include <IWebCore>

extern const char MySqlDbConnection[];

class MySqlDb : public IOrmDatabaseInterface<MySqlDb, false>
{
    $AsDatabase(MySqlDb)
public:
    MySqlDb() = default;

public:
    virtual IOrmDataSource configDataSource() final;
    virtual void registerEntities() final;
};
