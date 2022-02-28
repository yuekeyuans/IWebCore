#pragma once

#include "base/IHeaderUtil.h"
#include "orm/IOrmManage.h"
#include "orm/database/IOrmDataSource.h"
#include "orm/private/IOrmDatabaseWareImpl.h"

$PackageWebCoreBegin

class IOrmTableInfo;
class IOrmDatabaseWareImpl;

class IOrmDatabaseWare
{
public:
    IOrmDatabaseWare();
    virtual ~IOrmDatabaseWare();
    virtual IOrmDataSource configDataSource() {return {};};
//    virtual QSqlDatabase   createDataBase();
    virtual void           closeDataBase();
    virtual void registerTables() =0;

    QSqlDatabase&           getDatabase() const;
    const QStringList&      getTables() const;
    const QString&          getDriverName() const;
    const QString&          getConnectionName() const;
    const IOrmDataSource&   getDataSource() const;

    virtual bool isDatabaseOpend();
    virtual void openDatabase();
    virtual void closeDatabase();

    template<class T>
    void registerTable(const QString& sql = "");

protected:
    friend class IOrmDatabaseWareImpl;
    std::shared_ptr<IOrmDatabaseWareImpl> pimpl;
};

template<class T>
void IOrmDatabaseWare::registerTable(const QString &sql)
{
    pimpl->registerTable(T::tableInfo(), sql);
}


$PackageWebCoreEnd
