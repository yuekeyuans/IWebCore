#pragma once

#include "base/IPreProcessorUtil.h"
#include "orm/IOrmPreProcessor.h"
#include "orm/dialect/IOrmDialectInterface.h"

$PackageWebCoreBegin

class IOrmSqliteDialect : public IOrmDialectInterface<IOrmSqliteDialect>
{
    $AsDialect(IOrmSqliteDialect)
private:
    IOrmSqliteDialect() = default;
public:
    virtual QString dialectType() final;
    virtual bool insert(QSqlDatabase& db, IOrmTableWare& table, const QStringList& columns = {}) final;
    virtual QString getSqlType(const int typeId) final;
    virtual QString getLimitString(int count) final;
    virtual QString getLimitString(quint64 start, quint64 count) final;

private:
    QVariant getInsertedPrimaryKey(QSqlDatabase& query, IOrmTableWare &table, const QVariant& rowid);
    virtual bool truncateTable(QSqlDatabase &db, const IOrmTableInfo &info) final;
};

$PackageWebCoreEnd
