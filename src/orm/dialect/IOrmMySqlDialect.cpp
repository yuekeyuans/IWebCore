#include "IOrmMySqlDialect.h"
#include "orm/IOrmManage.h"
#include "orm/tableview/IOrmTableInfo.h"
#include "orm/tableview/IOrmEntityWare.h"
#include "orm/tableview/IOrmTableWare.h"
#include "orm/tableview/IOrmViewWare.h"

$PackageWebCoreBegin

IOrmMySqlDialect::IOrmMySqlDialect()
{
}

QString IOrmMySqlDialect::dialectType()
{
    return "QMYSQL";
}

QString IOrmMySqlDialect::getSqlType(const int typeId)
{
    static const QMap<int, QString> map = {
        {QMetaType::Char, "INTEGER"},
        {QMetaType::UChar, "INTEGER"},
        {QMetaType::Short, "INTEGER"},
        {QMetaType::UShort, "INTEGER"},
        {QMetaType::Int, "INTEGER"},
        {QMetaType::UInt, "INTEGER"},
        {QMetaType::Long, "INTEGER"},
        {QMetaType::ULong, "INTEGER"},
        {QMetaType::LongLong, "INTEGER"},
        {QMetaType::ULongLong, "INTEGER"},
        {QMetaType::Double, "DOUBLE"},
        {QMetaType::Float, "FLOAT"},

        {QVariant::String, "VARCHAR(100)"}, // TODO: 这个需要修改

        {QVariant::Bool, "BOOL"},

        {QVariant::Date, "DATE"},
        {QVariant::Time, "TIME(3)"},
        {QVariant::DateTime, "DATETIME(3)"}
    };
    if(!map.contains(typeId)){
        QString info = QString("Type is not supported. Type:").append(QVariant::typeToName(typeId));
        qFatal(info.toUtf8());
    }
    return map[typeId];
}

QString IOrmMySqlDialect::getLimitString(int count)
{
    return QString("LIMIT ").append(QString::number(count));
}

QString IOrmMySqlDialect::getLimitString(quint64 start, quint64 count)
{
    return QString("LIMIT ").append(QString::number(start)).append(" ,").append(QString::number(count));
}

bool IOrmMySqlDialect::insert(QSqlDatabase &db, IOrmTableWare &table, const QStringList &columns)
{
    ISqlQuery query(db);
    const auto info = table.getOrmEntityInfo();
    auto sql = getInsertSqlClause(*info, columns);
    query.prepare(sql);

    bool isKeyInserted = false;

    for(const auto& fieldName : columns){
        auto originVale = table.getFieldValue(fieldName);
        auto decoratedValue = decorateValue(*info, fieldName, originVale);
        query.bindValue(":" + fieldName, decoratedValue);
        if(info->primaryKey == fieldName && originVale.type() == QVariant::String){
            table.setFieldValue(info->primaryKey, decoratedValue);
            isKeyInserted = true;
        }
    }
    auto result = query.exec();
    if(!result){
        qDebug() << query.lastError();
        return result;
    }

    if(!isKeyInserted && !info->autoGenerateKey.isEmpty()){
        auto rowid = query.lastInsertId();
        table.setFieldValue(info->autoGenerateKey, rowid);
    }
    return result;
}

QString IOrmMySqlDialect::createSqlCommonKeyClause(const IOrmTableInfo &info, const QString &name)
{
    auto typeId = info.fieldTypeIds[info.fieldNames.indexOf(name)];
    auto sqlType = info.getFieldSqlType(name);  // sql type
    if(sqlType.isEmpty()){
        sqlType = getSqlType(typeId);
    }

    QString piece = name + " " + sqlType;

    if(info.notNullNKeys.contains(name)){
        piece.append(" NOT NULL");
    }

    if(info.uniqueKeys.contains(name)){
        piece.append(" UNIQUE");
    }

    if(info.primaryKey == name){
        piece.append(" PRIMARY KEY");
    }

    if(info.autoGenerateKey == name && info.autoGenerateType == "default"){
        auto typeId = info.getFieldTypeId(name);
        if(typeId != QMetaType::QString && IToeUtil::isPrimaryKeyType(typeId)){
            piece.append(" AUTO_INCREMENT");
        }
    }
    return piece;
}

$PackageWebCoreEnd
