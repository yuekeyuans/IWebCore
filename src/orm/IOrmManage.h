#pragma once
#include "core/base/IPreProcessorUtil.h"
#include "core/unit/ISingletonUnit.h"

#include "orm/database/IOrmDataSource.h"
#include "orm/dialect/IOrmDialectWare.h"

$PackageWebCoreBegin

class IOrmDatabaseWare;

class IOrmManage : public ISingletonUnit<IOrmManage>
{
    friend struct ISingletonUnit<IOrmManage>;
private:
    IOrmManage();

public:
    using GeneratorFunction = QVariant (*)(QMetaType::Type, const QString& stratgy);
    using QueryLogFunction  = void (*)(const QSqlQuery&);

    // 自动生成序列
    static QVariant autoGeneratFieldValue(QMetaType::Type type, const QString& stratgy);
    static void logQuery(const QSqlQuery& query);

    static QSqlDatabase& getDataBase(const QString& dbName);
    static void registerDataBase(IOrmDatabaseWare* db);
    static void registerDataBase(const QString& dbName, IOrmDatabaseWare* db);

    static void unregisterDatabase(IOrmDatabaseWare* db);
    static void unregisterDatabase(const QString& dbName = "defalut");

    static IOrmDataSource getDataSource(const QString& name = "default");
    static IOrmDialectWare* getDialect(const QString& name);
    static void registerDialect(IOrmDialectWare* dialect);

    static void registerValueGenerator(QMetaType::Type, const QString& stratgy,  GeneratorFunction fun);
    static void registerQueryLog(QueryLogFunction);

private:
    void registerDefaultValueGenerator();
    void registerDefaultQueryLog();

private:
    QMap<QMetaType::Type, QMap<QString, GeneratorFunction>> m_valueGeneratorMap;
    QList<QueryLogFunction> m_queryLogList;
    QMap<QString, IOrmDatabaseWare*> database;
    QMap<QString, IOrmDialectWare*> dialects;
};

$PackageWebCoreEnd
