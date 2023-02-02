#include "IOrmUtil.h"
#include "core/base/IToeUtil.h"
#include "core/base/IConvertUtil.h"
#include "core/base/IConstantUtil.h"
#include "core/base/IJsonUtil.h"
#include "orm/tableview/IOrmTableInfo.h"

$PackageWebCoreBegin

QVariant get_single_row_single_col_variant(QSqlQuery& query, bool*ok) {

#ifdef QT_DEBUG
    const auto& fields = IOrmUtil::getFieldNames(query);
    if(fields.length() != 1){
        QString info = QString("in getXX function of query one parameter, the query result must be only one column. \n in sql:") + query.lastQuery();
        qFatal(info.toUtf8());
    }
#endif

    IToeUtil::setOk(ok, true);
    size_t count = 0;
    QVariant ret;
    while(query.next()){
        if(count == 0){
            ret = query.value(0);   // 只取第一个数据
        }
        count ++;
    }
    IToeUtil::setOk(count != 1 && ok != nullptr, ok, false);
    return ret;
};

QList<QVariant> get_multi_row_single_col_variant(QSqlQuery& query, bool*ok)
{
#ifdef QT_DEBUG
    const auto& fields = IOrmUtil::getFieldNames(query);
    if(fields.length() != 1){
        QString info = "in getXX function of query one column, the query result must be only one column. \n in sql:" + query.lastQuery();
        qFatal(info.toUtf8());
    }
#endif

    IToeUtil::setOk(ok, true);
    QList<QVariant> ret;
    while(query.next()){
        ret.append(query.value(0));
    }
    return ret;
};



int IOrmUtil::getInt(QSqlQuery &query, bool *ok)
{
    bool convertOk;
    int value = get_single_row_single_col_variant(query, ok).toInt(&convertOk);
    IToeUtil::setOkAnd(ok, convertOk);
    return value;
}

uint IOrmUtil::getUint(QSqlQuery &query, bool *ok)
{
    bool convertOk;
    uint value = get_single_row_single_col_variant(query, ok).toUInt(&convertOk);
    IToeUtil::setOkAnd(ok, convertOk);
    return value;
}

qulonglong IOrmUtil::getULongLong(QSqlQuery &query, bool *ok)
{
    bool convertOk;
    qulonglong value = get_single_row_single_col_variant(query, ok).toULongLong(&convertOk);
    IToeUtil::setOkAnd(ok, convertOk);
    return value;
}

qlonglong IOrmUtil::getLongLong(QSqlQuery &query, bool *ok)
{
    bool convertOk;
    qlonglong value = get_single_row_single_col_variant(query, ok).toLongLong(&convertOk);
    IToeUtil::setOkAnd(ok, convertOk);
    return value;
}

float IOrmUtil::getFloat(QSqlQuery &query, bool *ok)
{
    bool convertOk;
    float value = get_single_row_single_col_variant(query, ok).toFloat(&convertOk);
    IToeUtil::setOkAnd(ok, convertOk);
    return value;
}

double IOrmUtil::getDouble(QSqlQuery &query, bool *ok)
{
    bool convertOk;
    double value = get_single_row_single_col_variant(query, ok).toDouble(&convertOk);
    IToeUtil::setOkAnd(ok, convertOk);
    return value;
}

// NOTE: 在 orm 实现中 , bool 实现使用 integral 类型， 1 为 true， 0 为false, 可以使用 falsy, 和 truthy 解析
bool IOrmUtil::getBool(QSqlQuery &query, bool *ok)
{
    int value = get_single_row_single_col_variant(query, ok).toBool();;
    return value;
}

QString IOrmUtil::getString(QSqlQuery &query, bool *ok)
{
    return get_single_row_single_col_variant(query, ok).toString();
}

QDate IOrmUtil::getDate(QSqlQuery &query, bool *ok)
{
    IToeUtil::setOk(ok, true);
    bool convertOk;
    auto val = get_single_row_single_col_variant(query, &convertOk);
    IToeUtil::setOkAnd(ok, convertOk);
    if(!convertOk){
        return QDate();
    }
    switch (val.type()) {
    case QVariant::Date:
        return val.toDate();
    case QVariant::DateTime:
        return val.toDateTime().date();
    case QVariant::String:
        return IConvertUtil::toDate(val.toString());
    case QVariant::Invalid:
        return QDate();
    default:
        qFatal("error");
    }
    return QDate();
}

QTime IOrmUtil::getTime(QSqlQuery &query,  bool *ok)
{
    IToeUtil::setOk(ok, true);
    bool convertOk;
    auto val = get_single_row_single_col_variant(query, &convertOk);
    IToeUtil::setOkAnd(ok, convertOk);
    if(!convertOk){
        return QTime();
    }
    switch (val.type()) {
    case QVariant::Time:
        return val.toTime();
    case QVariant::DateTime:
        return val.toDateTime().time();
    case QVariant::String:
        return IConvertUtil::toTime(val.toString());
    case QVariant::Invalid:
        return QTime();
    default:
        qFatal("error");
    }
    return QTime();
}

QDateTime IOrmUtil::getDateTime(QSqlQuery &query, bool *ok)
{
    IToeUtil::setOk(ok, true);
    bool convertOk;
    auto val = get_single_row_single_col_variant(query, &convertOk);
    IToeUtil::setOkAnd(ok, convertOk);
    if(!convertOk){
        return QDateTime();
    }
    switch (val.type()) {
    case QVariant::DateTime:
        return val.toDateTime();
    case QVariant::String:
        return IConvertUtil::toDateTime(val.toString());
    case QVariant::Invalid:
        return QDateTime();
    default:
        qFatal("error");
    }
    return QDateTime();
}

QVariant IOrmUtil::getVariant(QSqlQuery &query, bool *ok)
{
    return get_single_row_single_col_variant(query, ok);
}

QMap<QString, QVariant> IOrmUtil::getMap(QSqlQuery &query, bool *ok)
{
    QMap<QString, QVariant> map;
    size_t count = 0;
    auto fields = getFieldNames(query);
    while(query.next()){
        count ++;
        for(const auto& field : fields){
            map[field] = query.value(field);
        }
    }
    IToeUtil::setOk(ok, count == 1);
    return map;
}

QJsonObject IOrmUtil::getJsonObject(QSqlQuery &query, bool *ok)
{
    QJsonObject obj;
    size_t count = 0;
    auto fields = getFieldNames(query);
    while(query.next()){
        count ++;
        for(const auto& field : fields){
            obj[field] = IConvertUtil::toJsonValue(query.value(field));
        }
    }
    IToeUtil::setOk(ok, count == 1);
    return obj;
}

QList<QMap<QString, QVariant> > IOrmUtil::getMapList(QSqlQuery &query)
{
    QList<QMap<QString, QVariant>> ret;
    auto fields = getFieldNames(query);
    while(query.next()){
        QMap<QString, QVariant> map;
        for(const auto& field : fields){
            map[field] = query.value(field);
        }
        ret.append(std::move(map));
    }
    return ret;
}

QJsonArray IOrmUtil::getJsonObjectArray(QSqlQuery &query)
{
    QJsonArray ret;
    auto fields = getFieldNames(query);
    while(query.next()){
        QJsonObject obj;
        for(const auto& field : fields){
            obj[field] = IConvertUtil::toJsonValue(query.value(field));
        }
        ret.append(std::move(obj));
    }
    return ret;
}

QList<QVariant> IOrmUtil::getVariantList(QSqlQuery &query, bool *ok)
{
    return get_multi_row_single_col_variant(query, ok);
}

QList<int> IOrmUtil::getIntList(QSqlQuery &query, bool *ok)
{
    QList<int> ret;
    auto result = get_multi_row_single_col_variant(query, ok);
    bool convertOk;
    for(const auto& val : result){
        ret.append(val.toInt(&convertOk));
        IToeUtil::setOkAnd(ok, convertOk);
    }
    return ret;
}

QList<uint> IOrmUtil::getUintList(QSqlQuery &query, bool *ok)
{
    QList<uint> ret;
    auto result = get_multi_row_single_col_variant(query, ok);
    bool convertOk;
    for(const auto& val : result){
        ret.append(val.toUInt(&convertOk));
        IToeUtil::setOkAnd(ok, convertOk);
    }
    return ret;
}

QList<qulonglong> IOrmUtil::getULongLongList(QSqlQuery &query, bool *ok)
{
    QList<qulonglong> ret;
    auto result = get_multi_row_single_col_variant(query, ok);
    bool convertOk;
    for(const auto& val : result){
        ret.append(val.toULongLong(&convertOk));
        IToeUtil::setOkAnd(ok, convertOk);
    }
    return ret;
}

QList<qlonglong> IOrmUtil::getLongLongList(QSqlQuery &query, bool *ok)
{
    QList<qlonglong> ret;
    auto result = get_multi_row_single_col_variant(query, ok);
    bool convertOk;
    for(const auto& val : result){
        ret.append(val.toLongLong(&convertOk));
        IToeUtil::setOkAnd(ok, convertOk);
    }
    return ret;
}

QList<float> IOrmUtil::getFloatList(QSqlQuery &query, bool *ok)
{
    QList<float> ret;
    auto result = get_multi_row_single_col_variant(query, ok);
    bool convertOk;
    for(const auto& val : result){
        ret.append(val.toFloat(&convertOk));
        IToeUtil::setOkAnd(ok, convertOk);
    }
    return ret;
}

QList<double> IOrmUtil::getDoubleList(QSqlQuery &query, bool *ok)
{
    QList<double> ret;
    auto result = get_multi_row_single_col_variant(query, ok);
    bool convertOk;
    for(const auto& val : result){
        ret.append(val.toDouble(&convertOk));
        IToeUtil::setOkAnd(ok, convertOk);
    }
    return ret;
}

QList<bool> IOrmUtil::getBoolList(QSqlQuery &query, bool *ok)
{
    QList<bool> ret;
    auto result = get_multi_row_single_col_variant(query, ok);
    bool convertOk;
    for(const auto& val : result){
        auto value = val.toInt(&convertOk);
        ret.append(value != 0);
        IToeUtil::setOkAnd(ok, convertOk);
    }
    return ret;
}

QStringList IOrmUtil::getStringList(QSqlQuery &query, bool *ok)
{
    QStringList ret;
    auto result = get_multi_row_single_col_variant(query, ok);
    for(const auto& val : result){
        ret.append(val.toString());
    }
    return ret;
}


QStringList IOrmUtil::getFieldNames(const IOrmEntityInfoWare &info, const QStringList &keys)
{
    QStringList fields;

    const auto& names = info.fieldNames;
    for(const auto& name : names){  // 直接n^2, 不排序
        if(keys.contains(name)){
            fields.append(name);
        }
    }
    return fields;
}


QStringList IOrmUtil::getFieldNames(const QVector<QMetaProperty> &props, const QStringList &keys)
{
    QStringList fields;
    for(const auto& prop : props){
        QString name = prop.name();
        if(keys.contains(name)){
            fields.append(name);
        }
    }
    return fields;
}

QStringList IOrmUtil::getFieldNames(const IOrmEntityInfoWare &info)
{
    return info.fieldNames;
}

QStringList IOrmUtil::getFieldNames(const QSqlQuery &query)
{
    QStringList fields;
    auto record = query.record();
    auto count = record.count();
    for(int i=0; i<count; i++){
        fields.append(record.fieldName(i));
    }
    return fields;
}

QStringList IOrmUtil::getFieldNames(const QSqlQuery &query, const IOrmEntityInfoWare &info)
{
    const QSqlRecord& record = query.record();
    const QStringList& fields = info.fieldNames;
    QStringList validField;
    for(const auto& field : fields){
        if(record.contains(field)){
            validField.append(field);
        }
    }
    return validField;
}

// TODO: 怎样处理异常数据
QList<QDate> IOrmUtil::getDateList(QSqlQuery &query, bool *ok)
{
    QList<QDate> dates;
    auto result = get_multi_row_single_col_variant(query, ok);
    for(const QVariant& val : result){
        switch (val.type()) {
        case QVariant::Date:
            dates.append(val.toDate());
            break;
        case QVariant::DateTime:
            dates.append(val.toDateTime().date());
            break;
        case QVariant::String:
            dates.append(IConvertUtil::toDate(val.toString()));
            break;
        case QVariant::Invalid:
            dates.append(QDate());
            break;
        default:
            qFatal("current other type of date not supported");
        }
    }
    return dates;
}

// TODO: 这里用不到 dialect 的原因是 规定死 time 的格式，只能是这几种，就不需要dialect 配置了。
QList<QTime> IOrmUtil::getTimeList(QSqlQuery &query, bool *ok)
{
    QList<QTime> ret;
    auto result = get_multi_row_single_col_variant(query, ok);
    for(const QVariant& val : result){
        switch (val.type()) {
        case QVariant::DateTime:
            ret.append(val.toDateTime().time());
            break;
        case QVariant::Time:
            ret.append(val.toTime());
            break;
        case QVariant::String:
            ret.append(IConvertUtil::toTime(val.toString()));
            break;
        case QVariant::Invalid:
            ret.append(QTime());
            break;
        default:
            qFatal("current other type of date not supported");
        }
    }
    return ret;
}

QList<QDateTime> IOrmUtil::getDateTimeList(QSqlQuery &query, bool *ok)
{
    QList<QDateTime> ret;
    auto result = get_multi_row_single_col_variant(query, ok);
    for(const QVariant& val : result){
        switch (val.type()) {
        case QVariant::DateTime:
            ret.append(val.toDateTime());
            break;
        case QVariant::String:
            ret.append(IConvertUtil::toDateTime(val.toString()));
            break;
        case QVariant::Invalid:
            ret.append(QDateTime());
            break;
        default:
            qFatal("current other type of date not supported");
        }
    }
    return ret;
}

QMap<QString, QVariant> IOrmUtil::toMap(const QJsonObject &obj, bool *ok)
{
    return IConvertUtil::toMap(IConvertUtil::toVariant(obj, ok), ok);
}

QList<QMap<QString, QVariant>> IOrmUtil::toMapList(const QJsonArray &array, bool *ok)
{
    IToeUtil::setOk(ok, true);
    QList<QMap<QString, QVariant>>  ret;
    bool convertOk;
    for(const QJsonValue& value : array){
        if(!value.isObject()){
            IToeUtil::setOk(ok, false);
            return ret;
        }
        ret.append(IOrmUtil::toMap(value.toObject(), &convertOk));
        IToeUtil::setOkAnd(ok, convertOk);
    }
    return ret;
}

$PackageWebCoreEnd
