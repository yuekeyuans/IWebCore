#include "IOrmDatabaseWare.h"
#include "orm/tableview/IOrmTableInfo.h"

$PackageWebCoreBegin

IOrmDatabaseWare::IOrmDatabaseWare()
    : pimpl(std::make_shared<IOrmDatabaseWareImpl>())
{
}

IOrmDatabaseWare::~IOrmDatabaseWare()
{
    pimpl->closeDatabase();
}

void IOrmDatabaseWare::closeDataBase()
{
    return pimpl->closeDatabase();
}

QSqlDatabase& IOrmDatabaseWare::getDatabase() const
{
    return pimpl->m_db;
}

const QStringList &IOrmDatabaseWare::getTables() const
{
    return pimpl->m_tables;
}

const QString &IOrmDatabaseWare::getDriverName() const
{
    return pimpl->m_dataSource.driverName;
}

const QString &IOrmDatabaseWare::getConnectionName() const
{
    return pimpl->m_dataSource.connectionName;
}

const IOrmDataSource &IOrmDatabaseWare::getDataSource() const
{
    return pimpl->m_dataSource;
}

bool IOrmDatabaseWare::isDatabaseOpend()
{
    if(pimpl->m_db.isValid() && pimpl->m_db.isOpen()){
        return true;
    }
    return false;
}

void IOrmDatabaseWare::openDatabase()
{
    if(!isDatabaseOpend()){
        auto dataSource = configDataSource();
        pimpl->openDatabase(dataSource);
        registerTables();
    }
}

void IOrmDatabaseWare::closeDatabase()
{
    pimpl->closeDatabase();
}

$PackageWebCoreEnd
