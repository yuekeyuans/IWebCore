#pragma once

#include <IWebCore>

extern const char MySqlWorldConnectionName[];

/**
 * @brief The MySqlWorldDatabase class
 * 本电脑上没有安装 mysql, 所以 disable 掉，其实原理都一样
 */

class MySqlWorldDatabase : public IOrmDatabaseInterface<MySqlWorldDatabase, false>
{
    Q_GADGET
    $AsDatabase(MySqlWorldDatabase)
public:
    MySqlWorldDatabase();

public:
    virtual IOrmDataSource configDataSource() final;
    virtual void registerEntities() final;
};

