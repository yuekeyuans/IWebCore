#pragma once

#include "base/IHeaderUtil.h"
#include "base/IToeUtil.h"

$PackageWebCoreBegin

class IOrmTableInfo;
namespace IOrmUtil
{
// 单行单列 获取
    int getInt(QSqlQuery& query, bool* ok=nullptr);
    uint getUint(QSqlQuery& query, bool* ok=nullptr);
    qulonglong getULongLong(QSqlQuery& query, bool* ok=nullptr);
    qlonglong getLongLong(QSqlQuery& query, bool* ok=nullptr);
    float getFloat(QSqlQuery& query, bool* ok=nullptr);
    double getDouble(QSqlQuery& query, bool* ok=nullptr);
    bool getBool(QSqlQuery& query, bool* ok=nullptr);
    QString getString(QSqlQuery& query, bool* ok=nullptr);
    QVariant getVariant(QSqlQuery& query, bool *ok=nullptr);
    QDate getDate(QSqlQuery& query, bool* ok=nullptr);
    QTime getTime(QSqlQuery& query, bool* ok=nullptr);
    QDateTime getDateTime(QSqlQuery& query, bool* ok=nullptr);

// 单行多列 获取
    QMap<QString, QVariant> getMap(QSqlQuery& query, bool* ok=nullptr);
    QJsonObject getJsonObject(QSqlQuery& query, bool* ok=nullptr);
    template <class T> T getBean(QSqlQuery& query);

// 多行多列 获取
    QList<QMap<QString, QVariant>> getMapList(QSqlQuery& query);
    QJsonArray getJsonObjectArray(QSqlQuery& query);
    template <class T> QList<T> getBeans(QSqlQuery& query);

// 多行单列 获取
    QList<QVariant> getVariantList(QSqlQuery& query, bool* ok=nullptr);
    QList<int> getIntList(QSqlQuery& query, bool* ok=nullptr);
    QList<uint> getUintList(QSqlQuery& query, bool* ok=nullptr);
    QList<qulonglong> getULongLongList(QSqlQuery& query, bool* ok=nullptr);
    QList<qlonglong> getLongLongList(QSqlQuery& query, bool* ok=nullptr);
    QList<float> getFloatList(QSqlQuery& query, bool* ok=nullptr);
    QList<double> getDoubleList(QSqlQuery& query, bool* ok=nullptr);
    QList<bool> getBoolList(QSqlQuery& query, bool* ok=nullptr);
    QStringList getStringList(QSqlQuery& query, bool* ok=nullptr);
    QList<QDate> getDateList(QSqlQuery& query, bool* ok=nullptr);
    QList<QTime> getTimeList(QSqlQuery& query, bool* ok=nullptr);
    QList<QDateTime> getDateTimeList(QSqlQuery& query, bool* ok=nullptr);

// toXX 转换  (bean, QJsonObject， map, list 互相转换)
    template <class T>
    QJsonObject toJsonObject(const T& bean, bool*ok = nullptr);

    template <class T>
    QJsonArray toJsonQbjectArray(const QList<T>&, bool*ok = nullptr);

    template <class T>
    QMap<QString, QVariant> toMap(const T& t, bool* ok=nullptr);
    QMap<QString, QVariant> toMap(const QJsonObject&, bool*ok = nullptr);

    template <class T>
    QList<QMap<QString, QVariant>> toMapList(QList<T>& list, bool* ok=nullptr);
    QList<QMap<QString, QVariant>> toMapList(const QJsonArray& array, bool* ok=nullptr);

    template <class T>
    T toBean(const QMap<QString, QVariant>& map, bool* ok=nullptr);

    template <class T>
    T toBean(const QJsonObject& obj, bool* ok=nullptr);

    template <class T>
    QList<T> toBeans(const QJsonArray& array, bool* ok=nullptr);

    template <class T>
    QList<T> toBeans(const QList<QMap<QString, QVariant>>&list, bool*ok=nullptr);

// util
    QStringList getFieldNames(const IOrmTableInfo& info);
    QStringList getFieldNames(const IOrmTableInfo& info, const QStringList& keys); // 求交集
    QStringList getFieldNames(const QVector<QMetaProperty>& props, const QStringList& keys);
    QStringList getFieldNames(const QSqlQuery& query);
    QStringList getFieldNames(const QSqlQuery& query, const IOrmTableInfo& info);
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
    const QStringList& validField = getFieldNames(query, T::tableInfo());

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
    const QStringList& validField = getFieldNames(query, T::tableInfo());

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
QJsonObject IOrmUtil::toJsonObject(const T &t, bool *ok)
{
    return IConvertUtil::toJsonObject(IOrmUtil::toMap<T>(t, ok));
}

template<class T>
QJsonArray IOrmUtil::toJsonQbjectArray(const QList<T> &list, bool* ok)
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
QMap<QString, QVariant> IOrmUtil::toMap(const T &t, bool *ok)
{
    IToeUtil::setOk(ok, true);

    QMap<QString, QVariant> ret;
    const auto& info = T::tableInfo();
    const auto& fields = IOrmUtil::getFieldNames(info);
    for(const auto& field : fields){
        ret[field] = t.getFieldValue(field);
    }
    return ret;
}

template<class T>
QList<QMap<QString, QVariant> > IOrmUtil::toMapList(QList<T> & list, bool *ok)
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
T IOrmUtil::toBean(const QMap<QString, QVariant> &map, bool *ok)
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
T IOrmUtil::toBean(const QJsonObject &obj, bool *ok)
{
    const auto& map = IOrmUtil::toMap(obj, ok);
    bool convertOk;
    auto val = toBean<T>(map, &convertOk);
    IToeUtil::setOkAnd(ok, convertOk);
    return val;
}

template<class T>
QList<T> IOrmUtil::toBeans(const QList<QMap<QString, QVariant> > &list, bool *ok)
{
    IToeUtil::setOk(ok, true);
    QList<T> ret;
    bool convertOk;
    for(const auto& map : list){
        ret.append(toBean<T>(map, &convertOk));
        IToeUtil::setOkAnd(ok, convertOk);
    }
    return ret;
}

template<class T>
QList<T> IOrmUtil::toBeans(const QJsonArray &array, bool *ok)
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
