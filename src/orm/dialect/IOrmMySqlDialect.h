#pragma once

#include "orm/IOrmPreProcessor.h"
#include "orm/dialect/IOrmDialectInterface.h"

$PackageWebCoreBegin

class IOrmMySqlDialect : public IOrmDialectInterface<IOrmMySqlDialect>
{
    $AsDialect(IOrmMySqlDialect)
public:
    IOrmMySqlDialect();

    virtual QString dialectType() final;
    virtual QString getSqlType(const int typeId) final;
    virtual QString getLimitString(int count) final;
    virtual QString getLimitString(quint64 start, quint64 count) final;

    virtual bool insert(QSqlDatabase &db, IOrmTableWare &table, const QStringList &columns) final;
    virtual QString createSqlCommonKeyClause(const IOrmTableInfo &table, const QString &name) final;
};

$PackageWebCoreEnd
