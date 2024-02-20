#include "IJsonUtil_tojson.h"
#include "core/base/IConvertUtil.h"

$PackageWebCoreBegin

template<class T>
QJsonValue IJsonUtil::_objectToJson(const QList<T>& sequence)
{
    QJsonArray array;
    for(auto it = sequence.cbegin(); it != sequence.cend(); ++it){
        array.append(_objectToJson(*it));
    }
    return array;
}

template<class T>
QJsonValue IJsonUtil::_objectToJson(const QLinkedList<T>& sequence)
{
    QJsonArray array;
    for(auto it=sequence.cbegin(); it!=sequence.cend(); it++){
        array.append(_objectToJson(*it));
    }
    return array;
}

template<class T>
QJsonValue IJsonUtil::_objectToJson(const QStack<T>& sequence)
{
    QJsonArray array;
    for(auto it=sequence.cbegin(); it!=sequence.cend(); it++){
        array.append(_objectToJson(*it));
    }
    return array;
}

template<class T>
QJsonValue IJsonUtil::_objectToJson(const QQueue<T>& sequence)
{
    QJsonArray array;
    for(auto it=sequence.cbegin(); it!=sequence.cend(); it++){
        array.append(_objectToJson(*it));
    }
    return array;
}

template<class T>
QJsonValue IJsonUtil::_objectToJson(const QVector<T>& sequence)
{
    QJsonArray array;
    for(auto it=sequence.cbegin(); it!=sequence.cend(); it++){
        array.append(_objectToJson(*it));
    }
    return array;
}

template<class T>
QJsonValue IJsonUtil::_objectToJson(const std::list<T>& sequence)
{
    QJsonArray array;
    for(auto it=sequence.cbegin(); it!=sequence.cend(); it++){
        array.append(_objectToJson(*it));
    }
    return array;
}

template<class T>
QJsonValue IJsonUtil::_objectToJson(const std::vector<T>& sequence)
{
    QJsonArray array;
    for(auto it=sequence.cbegin(); it!=sequence.cend(); it++){
        array.append(_objectToJson(*it));
    }
    return array;
}

template<class T>
QJsonValue IJsonUtil::_objectToJson(const std::deque<T>& sequence)
{
    QJsonArray array;
    for(auto it=sequence.cbegin(); it!=sequence.cend(); it++){
        array.append(_objectToJson(*it));
    }
    return array;
}

template<class T, int N>
QJsonValue IJsonUtil::_objectToJson(const std::array<T, N>& sequence)
{
    QJsonArray array;
    for(auto it=sequence.cbegin(); it!=sequence.cend(); it++){
        array.append(_objectToJson(*it));
    }
    return array;
}

template<class T>
QJsonValue IJsonUtil::_objectToJson(const QMap<QString, T>& map){
    QJsonObject obj;
    auto keys = map.keys();
    for(auto key : keys){
        obj[key] = _objectToJson(map[key]);
    }
    return obj;
}

template<class T, class P>
QJsonValue IJsonUtil::_objectToJson(const QPair<T, P> &pair)
{
    QJsonObject obj;
    obj[IConvertUtil::toString(pair.first)] = _objectToJson(pair.second);
    return obj;
}

template<class T>
QJsonValue IJsonUtil::_objectToJson(const std::map<QString, T>& map){
    QJsonObject obj;
    for(const auto& it : map){
        obj[it.first] = _objectToJson<>(it.second);
    }
    return obj;
}

template <class T>
typename std::enable_if<ITraitHelper::IsNumber<T>::value, QJsonValue>::type
IJsonUtil::_objectToJson(const T& value)
{
    return value;
}

template<class T>
typename std::enable_if<ITraitHelper::is_bean<T>::value, QJsonValue>::type
IJsonUtil::_objectToJson(const T& value)
{
    return value.toJson();
}

$PackageWebCoreEnd
