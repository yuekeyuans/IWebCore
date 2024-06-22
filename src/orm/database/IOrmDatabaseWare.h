#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/task/ITaskWare.h"
#include "orm/database/IOrmDataSource.h"

$PackageWebCoreBegin

class IOrmTableInfo;
class IOrmViewInfo;
class IOrmDatabaseWareImpl;

namespace IOrmDatabaseWareProxy{
    void registerTable(std::shared_ptr<IOrmDatabaseWareImpl> pimpl, const IOrmTableInfo& info, const QString& sql);
    void registerView(std::shared_ptr<IOrmDatabaseWareImpl> pimpl, const IOrmViewInfo& info, const QString& sq);
}

class IOrmDatabaseWare : public ITaskWare
{
    friend class IOrmDatabaseWareImpl;
public:
    IOrmDatabaseWare();
    virtual ~IOrmDatabaseWare();
    virtual IOrmDataSource configDataSource() {return {};}
//    virtual QSqlDatabase   createDataBase();
    virtual void           closeDataBase();
    virtual void registerEntities() =0;

    QSqlDatabase&           getDatabase() const;
    const QStringList&      getTables() const;
    const QString&          getDriverName() const;
    const QString&          getConnectionName() const;
    const IOrmDataSource&   getDataSource() const;

    virtual bool isDatabaseOpend();
    virtual void openDatabase();
    virtual void closeDatabase();

    template<typename T>
    void registerTable(const QString& sql = "");

    template<typename T>
    void registerView(const QString& sql = "");

protected:
    std::shared_ptr<IOrmDatabaseWareImpl> pimpl;
};

template<typename T>
void IOrmDatabaseWare::registerTable(const QString &sql)
{
    IOrmDatabaseWareProxy::registerTable(pimpl, T::entityInfo(), sql);
}

template<typename T>
void IOrmDatabaseWare::registerView(const QString &sql)
{
    IOrmDatabaseWareProxy::registerView(pimpl, T::entityInfo(), sql);
}

$PackageWebCoreEnd
