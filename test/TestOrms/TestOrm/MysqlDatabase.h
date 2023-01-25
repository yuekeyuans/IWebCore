#pragma once

#include <IWebCore>

extern const char MySqlDatabaseConnectionName[];

class MysqlDatabase : public IOrmDatabaseInterface<MysqlDatabase>
{
    Q_GADGET
    $AsDatabase(MysqlDatabase)
public:
    MysqlDatabase() = default;
    virtual IOrmDataSource configDataSource() final;
    virtual void registerEntities() final;
};
