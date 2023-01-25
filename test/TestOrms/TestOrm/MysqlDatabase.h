#pragma once

#include <IWebCore>

extern const char MySqlDatabaseConnectionName[];

class MysqlDatabase : public IOrmDatabaseInterface<MysqlDatabase, false>
{
    Q_GADGET
    $AsDatabase(MysqlDatabase)
public:
    MysqlDatabase() = default;
    virtual IOrmDataSource configDataSource() final;
    virtual void registerEntities() final;
};
