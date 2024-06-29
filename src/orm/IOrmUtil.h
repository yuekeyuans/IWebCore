#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/util/IToeUtil.h"

$PackageWebCoreBegin

class IOrmEntityInfoWare;
namespace IOrmUtil
{
// 单行单列 获取
    int getInt(QSqlQuery& query, bool& ok);
    uint getUint(QSqlQuery& query, bool& ok);

    qulonglong getULongLong(QSqlQuery& query, bool& ok);
    qlonglong getLongLong(QSqlQuery& query, bool& ok);

    float getFloat(QSqlQuery& query, bool& ok);
    double getDouble(QSqlQuery& query, bool& ok);

    bool getBool(QSqlQuery& query, bool& ok);

    QString getString(QSqlQuery& query, bool& ok);

    QVariant getVariant(QSqlQuery& query, bool& ok);

    QDate getDate(QSqlQuery& query, bool& ok);
    QTime getTime(QSqlQuery& query, bool& ok);
    QDateTime getDateTime(QSqlQuery& query, bool& ok);

// 单行多列 获取
    QMap<QString, QVariant> getMap(QSqlQuery& query, bool& ok);
    QJsonObject getJsonObject(QSqlQuery& query, bool& ok);
    template <class T> T getBean(QSqlQuery& query);

// 多行多列 获取
    QList<QMap<QString, QVariant>> getMapList(QSqlQuery& query);
    QJsonArray getJsonObjectArray(QSqlQuery& query);
    template <class T> QList<T> getBeans(QSqlQuery& query);

// 多行单列 获取
    QList<QVariant> getVariantList(QSqlQuery& query, bool& ok);
    QList<int> getIntList(QSqlQuery& query, bool& ok);
    QList<uint> getUintList(QSqlQuery& query, bool& ok);
    QList<qulonglong> getULongLongList(QSqlQuery& query, bool& ok);
    QList<qlonglong> getLongLongList(QSqlQuery& query, bool& ok);
    QList<float> getFloatList(QSqlQuery& query, bool& ok);
    QList<double> getDoubleList(QSqlQuery& query, bool& ok);
    QList<bool> getBoolList(QSqlQuery& query, bool& ok);
    QStringList getStringList(QSqlQuery& query, bool& ok);
    QList<QDate> getDateList(QSqlQuery& query, bool& ok);
    QList<QTime> getTimeList(QSqlQuery& query, bool& ok);
    QList<QDateTime> getDateTimeList(QSqlQuery& query, bool& ok);

// toXX 转换  (bean, QJsonObject， map, list 互相转换)
    template <class T>
    QJsonObject toJsonObject(const T& bean, bool& ok);

    template <class T>
    QJsonArray toJsonQbjectArray(const QList<T>&, bool& ok);

    template <class T>
    QMap<QString, QVariant> toMap(const T& t, bool& ok);
    QMap<QString, QVariant> toMap(const QJsonObject&, bool& ok);

    template <class T>
    QList<QMap<QString, QVariant>> toMapList(QList<T>& list, bool& ok);
    QList<QMap<QString, QVariant>> toMapList(const QJsonArray& array, bool& ok);

    template <class T>
    T toBean(const QMap<QString, QVariant>& map, bool& ok);

    template <class T>
    T toBean(const QJsonObject& obj, bool& ok);

    template <class T>
    QList<T> toBeans(const QJsonArray& array, bool& ok);

    template <class T>
    QList<T> toBeans(const QList<QMap<QString, QVariant>>&list, bool& ok);

// util
    QStringList getFieldNames(const IOrmEntityInfoWare& info);
    QStringList getFieldNames(const IOrmEntityInfoWare& info, const QStringList& keys); // 求交集
    QStringList getFieldNames(const QVector<QMetaProperty>& props, const QStringList& keys);
    QStringList getFieldNames(const QSqlQuery& query);
    QStringList getFieldNames(const QSqlQuery& query, const IOrmEntityInfoWare& info);
};

namespace  IConvertUtil{
    using IOrmUtil::toMap;
    using IOrmUtil::toBean;
    using IOrmUtil::toBeans;
    using IOrmUtil::toMapList;
    using IOrmUtil::toJsonObject;
    using IOrmUtil::toJsonQbjectArray;
}

template<class T>
T IOrmUtil::getBean(QSqlQuery &query)
{
    size_t count = 0;
    const QStringList& validField = getFieldNames(query, T::entityInfo());

    T t;
    while(query.next()){
        count ++;
        for(const auto& field : validField){
            t.setFieldValue(field, query.value(field));
        }
    }
    return count == 1 ? t : T{};
}

template<class T>
QList<T> IOrmUtil::getBeans(QSqlQuery &query)
{
    const QStringList& validField = getFieldNames(query, T::entityInfo());

    QList<T> beans;
    while(query.next()){
        T t;
        for(const auto& field : validField){
            t.setFieldValue(field, query.value(field));
        }
        beans.append(std::move(t));
    }
    return beans;
}

template<class T>
QJsonObject IOrmUtil::toJsonObject(const T &t, bool& ok)
{
    return IConvertUtil::toJsonObject(IOrmUtil::toMap<T>(t, ok));
}

template<class T>
QJsonArray IOrmUtil::toJsonQbjectArray(const QList<T> &list, bool& ok)
{
    IToeUtil::setOk(ok, true);
    QJsonArray array;
    bool convertOk;
    for(const T& t : list){
        array.append(IOrmUtil::toJsonObject<T>(t, convertOk));
        IToeUtil::setOkAnd(ok, convertOk);
    }
    return array;
}

template<class T>
QMap<QString, QVariant> IOrmUtil::toMap(const T &t, bool& ok)
{
    IToeUtil::setOk(ok, true);

    QMap<QString, QVariant> ret;
    const auto& info = T::entityInfo();
    const auto& fields = IOrmUtil::getFieldNames(info);
    for(const auto& field : fields){
        ret[field] = t.getFieldValue(field);
    }
    return ret;
}

template<class T>
QList<QMap<QString, QVariant> > IOrmUtil::toMapList(QList<T> & list, bool& ok)
{
    IToeUtil::setOk(ok, true);
    QList<QMap<QString, QVariant>> ret;
    bool convertOk;
    for(const T& t : list){
        ret.append(IOrmUtil::toMap<T>(t, &convertOk));
        IToeUtil::setOkAnd(ok, convertOk);
    }
    return ret;
}

// TODO: 这里目前不支持复合类型
template<class T>
T IOrmUtil::toBean(const QMap<QString, QVariant> &map, bool& ok)
{
    IToeUtil::setOk(ok, true);
    T t;
    const auto& props = t.getMetaProperties();
    const auto& keys = map.keys();
    const auto& fields = getFieldNames(props, keys);

    for(const auto& field : fields){
        t.setFieldValue(field, map[field]);
    }
    return t;
}

template<class T>
T IOrmUtil::toBean(const QJsonObject &obj, bool& ok)
{
    const auto& map = IOrmUtil::toMap(obj, ok);
    bool convertOk;
    auto val = toBean<T>(map, &convertOk);
    IToeUtil::setOkAnd(ok, convertOk);
    return val;
}

template<class T>
QList<T> IOrmUtil::toBeans(const QList<QMap<QString, QVariant> > &list, bool& ok)
{
    ok = true;
    QList<T> ret;
    bool convertOk;
    for(const auto& map : list){
        ret.append(toBean<T>(map, &convertOk));
        IToeUtil::setOkAnd(ok, convertOk);
    }
    return ret;
}

template<class T>
QList<T> IOrmUtil::toBeans(const QJsonArray &array, bool& ok)
{
    IToeUtil::setOk(ok, true);
    QList<T> ret;
    bool convertOk;
    for(const QJsonValue& val : array){
        if(!val.isObject()){
            IToeUtil::setOk(ok, false);
            return ret;
        }
        ret.append(toBean<T>(val.toObject(), &convertOk));
        IToeUtil::setOkAnd(ok, convertOk);
    }
    return ret;
}

$PackageWebCoreEnd
