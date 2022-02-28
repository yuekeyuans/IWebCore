#pragma once

#include "base/IHeaderUtil.h"
#include "ITraitHelper.h"
#include <type_traits>
#include <deque>

$PackageWebCoreBegin
namespace IJsonUtil
{

QJsonValue _objectToJson(const QString& value);

QJsonValue _objectToJson(bool value);

template<class T>
QJsonValue _objectToJson(const QList<T>& sequence);

template<class T>
QJsonValue _objectToJson(const QLinkedList<T>& sequence);

template<class T>
QJsonValue _objectToJson(const QStack<T>& sequence);

template<class T>
QJsonValue _objectToJson(const QQueue<T>& sequence);

template<class T>
QJsonValue _objectToJson(const QVector<T>& sequence);

template<class T>
QJsonValue _objectToJson(const std::list<T>& sequence);

template<class T>
QJsonValue _objectToJson(const std::vector<T>& sequence);

template<class T>
QJsonValue _objectToJson(const std::deque<T>& sequence);

template<class T, int N>
QJsonValue _objectToJson(const std::array<T, N>& sequence);

template<class T>
QJsonValue _objectToJson(const QMap<QString, T>& map);

template<class T>
QJsonValue _objectToJson(const QMap<QString, T>& map);

template<class T>
QJsonValue _objectToJson(const std::map<QString, T>& map);

template <class T>
typename std::enable_if<ITraitHelper::IsNumber<T>::value, QJsonValue>::type
_objectToJson(const T& value);

template<class T>
typename std::enable_if<ITraitHelper::IsBean<T>::value, QJsonValue>::type
_objectToJson(const T& value);

};

$PackageWebCoreEnd

#include "IJsonUtil_tojson_impl.cpp"
