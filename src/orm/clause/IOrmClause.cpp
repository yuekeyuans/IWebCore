#include "IOrmClause.h"
#include "orm/dialect/IOrmDialectWare.h"
#include "orm/IOrmManage.h"

$PackageWebCoreBegin

IOrmClause::IOrmClause(QSqlDatabase& db, const IOrmTableInfo& table) : m_db(db), m_table(table)
{

}

IOrmDialectWare *IOrmClause::getDialect()
{
    return IOrmManage::getDialect(m_db.driverName());
}

$PackageWebCoreEnd
