#pragma once

#include "core/util/IHeaderUtil.h"
#include "orm/clause/IOrmCondition.h"

$PackageWebCoreBegin

class IOrmTableInfo;
class IOrmDialectWare;

class IOrmClause{
public:
    IOrmClause(QSqlDatabase& db, const IOrmTableInfo& table);
    IOrmCondition& condition(){ return m_condtion;};

protected:
    IOrmDialectWare* getDialect();

protected:
    IOrmCondition m_condtion;
    QSqlDatabase& m_db;
    const IOrmTableInfo& m_table;
};

$PackageWebCoreEnd
