#pragma once

#include "core/base/IHeaderUtil.h"
#include "ITraitUtil.h"
#include <type_traits>
//#include <deque>

$PackageWebCoreBegin
namespace IJsonUtil
{

QJsonValue _objectToJson(const QString& value, bool &ok);

QJsonValue _objectToJson(int value, bool &ok);

QJsonValue _objectToJson(float value, bool &ok);

QJsonValue _objectToJson(double value, bool &ok);

QJsonValue _objectToJson(bool value, bool &ok);

QJsonValue _objectToJson(QJsonValue value, bool &ok);

QJsonValue _objectToJson(QJsonArray value, bool &ok);

QJsonValue _objectToJson(QJsonObject value, bool &ok);

QJsonValue _objectToJson(std::string_view value, bool& ok);

template<class T>
QJsonValue _objectToJson(const QList<T>& sequence, bool &ok);

template<class T>
QJsonValue _objectToJson(const QStack<T>& sequence, bool &ok);

template<class T>
QJsonValue _objectToJson(const QQueue<T>& sequence, bool &ok);

template<class T>
QJsonValue _objectToJson(const QVector<T>& sequence, bool &ok);

template<class T>
QJsonValue _objectToJson(const std::list<T>& sequence, bool &ok);

template<class T>
QJsonValue _objectToJson(const std::vector<T>& sequence, bool &ok);

template<class T, int N>
QJsonValue _objectToJson(const std::array<T, N>& sequence, bool &ok);

template<class T>
QJsonValue _objectToJson(const QMap<QString, T>& map, bool &ok);

template<class T, class P>
QJsonValue _objectToJson(const QPair<T, P>& pair, bool &ok);

template<class T>
QJsonValue _objectToJson(const QMap<QString, T>& map, bool &ok);

template<class T>
QJsonValue _objectToJson(const std::map<QString, T>& map, bool &ok);

template <class T>
typename std::enable_if<std::is_arithmetic<T>::value, QJsonValue>::type
_objectToJson(const T& value, bool &ok);

template<class T>
typename std::enable_if<ITraitUtil::is_bean<T>::value, QJsonValue>::type
_objectToJson(const T& value, bool &ok);

}

$PackageWebCoreEnd

#include "IJsonUtil_tojson_impl.cpp"
