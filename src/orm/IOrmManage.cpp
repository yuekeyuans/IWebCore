#include "IOrmManage.h"
#include "core/base/IConvertUtil.h"
#include "core/context/IContextManage.h"
#include "orm/dialect/IOrmDialectWare.h"
#include "orm/database/IOrmDatabaseWare.h"

$PackageWebCoreBegin

IOrmManage::IOrmManage()
{
    // 注册默认的 ValueGenerator
    registerDefaultValueGenerator();
    registerDefaultQueryLog();
}

QVariant IOrmManage::autoGeneratFieldValue(QMetaType::Type type, const QString &stratgy)
{
    auto inst = instance();
    IOrmManage::GeneratorFunction fun = nullptr;
    if(inst->m_valueGeneratorMap.contains(type)){
        if(inst->m_valueGeneratorMap[type].contains(stratgy)){
            fun = inst->m_valueGeneratorMap[type][stratgy];
        }
    }
    if(fun == nullptr){
        QString info = "generator type defined in $AutoGenerator is not registered in system, please check it.\nt"
                     "type: " + stratgy;
        qFatal(info.toUtf8());
    }

    return fun(type, stratgy);
}

void IOrmManage::logQuery(const QSqlQuery &query)
{
    auto inst = instance();
    const auto& list = inst->m_queryLogList;
    for(auto& log : list){
        log(query);
    }
}

QSqlDatabase& IOrmManage::getDataBase(const QString &dbName)
{
    auto inst = instance();
    if(dbName.isEmpty()){
        return inst->database["default"]->getDatabase();
    }
    return inst->database[dbName]->getDatabase();
}

void IOrmManage::registerDataBase(IOrmDatabaseWare *db)
{
    registerDataBase("default", db);
}

void IOrmManage::registerDataBase(const QString &dbName, IOrmDatabaseWare *db)
{
    auto inst = instance();
    if(inst->database.contains(dbName)){
        qFatal("database already registered");
    }
    inst->database[dbName] = db;
}

void IOrmManage::unregisterDatabase(IOrmDatabaseWare *db)
{
    auto inst = instance();
    auto keys = inst->database.keys();
    for(auto key : keys){
        auto value = inst->database[key];
        if(value == db){
            inst->database.remove(key);
            break;
        }
    }
}

void IOrmManage::unregisterDatabase(const QString &dbName)
{
    auto inst = instance();
    if(inst->database.contains(dbName)){
        inst->database.remove(dbName);
    }
}

IOrmDataSource IOrmManage::getDataSource(const QString &name)
{
    auto path = QString("dataSource.").append(name);
    bool convertOk;
    auto bean = IContextManage::getBean<IOrmDataSource>(path, &convertOk);
    if(!convertOk){
        qFatal("datasource config error");
    }
    return bean;
}

IOrmDialectWare *IOrmManage::getDialect(const QString &name)
{
    auto inst = instance();
    if(!inst->dialects.contains(name)){
        qFatal("current dialect not exist");
    }
    return inst->dialects[name];
}

void IOrmManage::registerDialect(IOrmDialectWare *dialect)
{
    auto inst = instance();
    auto name = dialect->dialectType();
    if(inst->dialects.contains(name)){
        qFatal("dialect already registered");
    }
    inst->dialects[name] = dialect;
}

void IOrmManage::registerValueGenerator(QMetaType::Type type, const QString &stratgy, IOrmManage::GeneratorFunction fun)
{
    auto inst = instance();
    inst->m_valueGeneratorMap[type][stratgy] = fun;
}

void IOrmManage::registerQueryLog(QueryLogFunction queryLog)
{
    auto inst = instance();
    if(!inst->m_queryLogList.contains(queryLog)){
        inst->m_queryLogList.append(queryLog);
    }
}

void IOrmManage::registerDefaultValueGenerator()
{
    static GeneratorFunction fun = [](QMetaType::Type, const QString& )->QVariant{
        return QUuid::createUuid().toString();
    };

    QMap<QString, IOrmManage::GeneratorFunction> generator;
    generator["default"] = fun;
    generator["uuid"] = fun;

    m_valueGeneratorMap[QMetaType::QString] = generator;
}

void IOrmManage::registerDefaultQueryLog()
{
    static QueryLogFunction log = [](const QSqlQuery& query){
        const QSqlError& error = query.lastError();
        if(error.type() != QSqlError::NoError){
            qDebug() << error;
        }

        qDebug() << query.lastQuery();
        const QMap<QString, QVariant>& values = query.boundValues();
        if(!values.isEmpty()){
            qDebug().noquote() << IConvertUtil::toString(values);
        }
    };
    m_queryLogList.append(log);
}

$PackageWebCoreEnd
