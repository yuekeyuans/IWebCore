#include "IOrmDatabaseWareImpl.h"

#include "orm/IOrmManage.h"
#include "orm/IOrmAssert.h"
#include "orm/tableview/IOrmTableInfo.h"
#include "orm/tableview/IOrmViewInfo.h"

$PackageWebCoreBegin

$UseAsset(IOrmAst)

bool IOrmDatabaseWareImpl::openDatabase(IOrmDataSource &datasource)
{
    m_dataSource = datasource;
    const auto& source = m_dataSource;

    if(source.driverName.isEmpty()){
        qFatal("diver name can not be empty");
    }

    if(source.connectionName.isEmpty()){
        m_db = QSqlDatabase::addDatabase(source.driverName, "default");
    }else {
        m_db = QSqlDatabase::addDatabase(source.driverName, source.connectionName);
    }
    if(!source.host.isEmpty()){
        m_db.setHostName(source.host);
    }
    if(source.port != -1){
        m_db.setPort(source.port);
    }
    if(!source.userName.isEmpty()){
        m_db.setUserName(source.userName);
    }
    if(!source.password.isEmpty()){
        m_db.setPassword(source.password);
    }
    if(!source.databaseName.isEmpty()){
        m_db.setDatabaseName(source.databaseName);
    }

    if(!m_db.open()){
        qFatal(m_db.lastError().text().toUtf8());
        return false;
    }

    m_existedTables = m_db.tables(QSql::Tables);
    m_existedViews =  m_db.tables(QSql::Views);
    return true;
}

void IOrmDatabaseWareImpl::closeDatabase()
{
    if(m_db.isValid() && m_db.isOpen()){
        QSqlDatabase::removeDatabase(m_db.connectionName());
        m_db.close();

    }
}

void IOrmDatabaseWareImpl::registerTable(const IOrmTableInfo &info, const QString &sql)
{
    checkTableInfo(info);
    auto tableName = info.entityName;
    if (m_existedTables.contains(tableName)) {
        return;
    }
    QString createSql = sql;
    if(sql.isEmpty()){
        QString driverName = m_dataSource.driverName;
        createSql = IOrmManage::getDialect(driverName)->createTableSqlClause(info);
    }
    execSql(createSql);
    m_tables.append(tableName);
}

void IOrmDatabaseWareImpl::registerView(const IOrmViewInfo &info, const QString &sql)
{
    checkViewInfo(info);
    auto viewName = info.entityName;
    if (m_existedViews.contains(viewName)) {
        return;
    }
    QString createSql = sql;
    if(sql.isEmpty()){
        IAssetInfo info;
        info.reason = QString("orm view ").append(viewName).append(" not exist, and no view create sql exist");
        $Ast->fatal("orm_view_can_not_be_created", info);
    }
    execSql(createSql);
    m_views.append(viewName);
}

void IOrmDatabaseWareImpl::execSql(const QString &sql)
{
    QSqlQuery result = m_db.exec(sql);
    if(result.lastError().isValid()){
        qDebug() << result.lastError();
    }
}

void IOrmDatabaseWareImpl::checkTableInfo(const IOrmTableInfo &info)
{
    if(info.fieldNames.length() == 0){
        qFatal("table has no argument");
    }
}

void IOrmDatabaseWareImpl::checkViewInfo(const IOrmViewInfo &info)
{
    if(info.fieldNames.length() == 0){
        qFatal("table has no argument");
    }
}

$PackageWebCoreEnd
