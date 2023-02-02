#include "IOrmTableInfo.h"

#include "core/base/IConstantUtil.h"
#include "orm/IOrmManage.h"

$PackageWebCoreBegin

namespace IOrmTableInfoHelper{
    using NotationFun = bool (*)(const QString& key, const QString& value, IOrmTableInfo& tableInfo);

    void obtainNotations(const QMap<QString, QString> clsInfo, IOrmTableInfo& tableInfo);
    const QList<NotationFun>& getNotationFun();
    bool setPrimaryKey(const QString& key, const QString& value, IOrmTableInfo& tableInfo);
    bool setUniqueKeys(const QString& key, const QString& value, IOrmTableInfo& tableInfo);
    bool setNotNullKeys(const QString& key, const QString& value, IOrmTableInfo& tableInfo);
    bool setAutoGenerateKeys(const QString& key, const QString& value, IOrmTableInfo& tableInfo);
    bool setSqlTypeKeys(const QString& key, const QString& value, IOrmTableInfo& tableInfo);

    void checkInfo(const QMap<QString, QString>& clsInfo, const IOrmTableInfo& tableInfo);
    void checkFieldTypes(const QMap<QString, QString>& clsInfo, const IOrmTableInfo& tableInfo);
    void checkDuplicatedPrimaryKey(const QMap<QString, QString>& clsInfo, const IOrmTableInfo& tableInfo);
    void checkAutoGenerateInfo(const QMap<QString, QString>& clsInfo, const IOrmTableInfo& tableInfo);
}

IOrmTableInfo::IOrmTableInfo(const QMetaObject &meta) : IOrmEntityInfoWare(meta)
{
    auto clsInfo = IMetaUtil::getMetaClassInfoMap(meta);
    IOrmTableInfoHelper::obtainNotations(clsInfo, *this);
    IOrmTableInfoHelper::checkInfo(clsInfo, *this);
}

void IOrmTableInfoHelper::obtainNotations(const QMap<QString, QString> clsInfo, IOrmTableInfo& tableInfo){
    const auto& notationFun = getNotationFun();
    for(const auto& name : clsInfo.keys()){
        const auto& value = clsInfo[name];
        for(auto fun : notationFun){
            if(fun(name, value, tableInfo)){
                break;
            }
        }
    }

    static const char* const Sql_AutoGenerateTypeClause = "autoIncrementType__";
    if(!tableInfo.autoGenerateKey.isEmpty()){
        QString name = QString(Sql_AutoGenerateTypeClause).append(tableInfo.autoGenerateKey);
        tableInfo.autoGenerateType = clsInfo[name];
    }
}

const QList<IOrmTableInfoHelper::NotationFun>& IOrmTableInfoHelper::getNotationFun(){
    static QList<NotationFun> notationFun = {
        IOrmTableInfoHelper::setPrimaryKey,
        IOrmTableInfoHelper::setUniqueKeys,
        IOrmTableInfoHelper::setNotNullKeys,
        IOrmTableInfoHelper::setSqlTypeKeys,
        IOrmTableInfoHelper::setAutoGenerateKeys
    };
    return notationFun;
}

bool IOrmTableInfoHelper::setPrimaryKey(const QString& key, const QString& value, IOrmTableInfo& tableInfo){
    static const char* const Sql_PrimayKeyClause = "primaryKey__";
    if(key.startsWith(Sql_PrimayKeyClause)){
        tableInfo.primaryKey = value;
        return true;
    }
    return false;
}

bool IOrmTableInfoHelper::setUniqueKeys(const QString& key, const QString& value, IOrmTableInfo& tableInfo){
    static const char* const Sql_UniqueKeyClause = "uniqueKey__";
    if(key.startsWith(Sql_UniqueKeyClause)){
        tableInfo.uniqueKeys.append(value);
        return true;
    }
    return false;
}

bool IOrmTableInfoHelper::setNotNullKeys(const QString& key, const QString& value, IOrmTableInfo& tableInfo){
    static const char* const Sql_NotNulKeyClause = "notNullKey__";
    if(key.startsWith(Sql_NotNulKeyClause)){
        tableInfo.notNullNKeys.append(value);
        return true;
    }
    return false;
}

bool IOrmTableInfoHelper::setSqlTypeKeys(const QString& key, const QString& value, IOrmTableInfo& tableInfo){
    static const char* const Sql_AutoGenerateKeyClause = "autoIncrementKey__";
    if(key.startsWith(Sql_AutoGenerateKeyClause)){
        tableInfo.autoGenerateKey = value;
        return true;
    }
    return false;
}

bool IOrmTableInfoHelper::setAutoGenerateKeys(const QString& key, const QString& value, IOrmTableInfo& tableInfo){
    static const char* const Sql_SqlTypeKeyClause = "sqlType__";
    if(key.startsWith(Sql_SqlTypeKeyClause)){
        auto fieldName = key.mid(QString(Sql_SqlTypeKeyClause).length());
        tableInfo.sqlType[fieldName] = value;
        return true;
    }
    return false;
}

void IOrmTableInfoHelper::checkInfo(const QMap<QString, QString> &clsInfo, const IOrmTableInfo& tableInfo)
{
    checkFieldTypes(clsInfo, tableInfo);
    checkDuplicatedPrimaryKey(clsInfo, tableInfo);
    checkAutoGenerateInfo(clsInfo, tableInfo);
}

void IOrmTableInfoHelper::checkFieldTypes(const QMap<QString, QString> &clsInfo, const IOrmTableInfo& tableInfo)
{
    Q_UNUSED(clsInfo)

    static QList<QMetaType::Type> allowTypes ={
        QMetaType::Bool,
        QMetaType::QString,
        QMetaType::Char, QMetaType::UChar,
        QMetaType::Short, QMetaType::UShort,
        QMetaType::Int, QMetaType::UInt,
        QMetaType::Long, QMetaType::ULong,
        QMetaType::LongLong, QMetaType::ULongLong,
        QMetaType::Double, QMetaType::Float,
        QMetaType::QDate, QMetaType::QTime, QMetaType::QDateTime,
    };
    const auto& fieldTypeIds = tableInfo.fieldTypeIds;
    for(const auto& typeId : fieldTypeIds){
        if(!allowTypes.contains(typeId)){
            QString info = QString("this kind of type is not supported in table, please change to the supported type. \n"
                                   "Type : ").append(QMetaType::typeName(typeId));
            qFatal(info.toUtf8());
        }
    }
}

void IOrmTableInfoHelper::checkDuplicatedPrimaryKey(const QMap<QString, QString> &clsInfo, const IOrmTableInfo& tableInfo)
{
    int index = 0;
    for(auto key : clsInfo.keys()){
        if(key.startsWith("primaryKey__")){
           index ++;
        }
    }
    if(index == 0){
        QString info = tableInfo.className + " table has no primary key, please add a primary key";
        qFatal(info.toUtf8());
    }else if(index > 1){
        QString info = tableInfo.className + " table has more than one primary key, one table can only has one primary key";
        qFatal(info.toUtf8());
    }
    auto pos = tableInfo.fieldNames.indexOf(tableInfo.primaryKey);
    auto typeId = tableInfo.fieldTypeIds[pos];
    if(!IToeUtil::isPrimaryKeyType(typeId)){
        QString info = tableInfo.className + " table has incorrect primary key annotated type. \n"
                                   "the only allowed type is int, long, longlong/int64, QString\n"
                                   "field:" + tableInfo.fieldNames[pos] + " type:" + tableInfo.fieldTypeNames[pos];
        qFatal(info.toUtf8());
    }
    if(typeId != QMetaType::QString && typeId != QMetaType::LongLong){
        QString info = QString("primary key that is number type recommended is qlonglong/qint64 type.\n"
                               "current is ").append(QMetaType::typeName(typeId)).append(" in class ").append(tableInfo.className);
        qWarning() << info;
    }
}

void IOrmTableInfoHelper::checkAutoGenerateInfo(const QMap<QString, QString> &clsInfo, const IOrmTableInfo& tableInfo)
{
    Q_UNUSED(clsInfo)
    static const char* const Sql_AutoGenerateKeyClause = "autoIncrementKey__";
    static QList<QMetaType::Type> allowTypes = {
        QMetaType::Int, QMetaType::LongLong, QMetaType::QString
    };

    if(!tableInfo.autoGenerateKey.isEmpty()){
        if(tableInfo.autoGenerateKey != tableInfo.primaryKey){
            QString info = tableInfo.className + " table: auto increment key must equal to primary key";
            qFatal(info.toUtf8());
        }
    }

    int index = 0;
    for(auto key : clsInfo.keys()){
        if(key.startsWith(Sql_AutoGenerateKeyClause)){
            index ++;
        }
    }
    if(index >1){
        QString info = tableInfo.className + " table: you can not have more than one increment note, please check";
        qFatal(info.toUtf8());
    }
}

$PackageWebCoreEnd
