//#include "IJsonUtil_tojson.h"
//#include "core/util/IConvertUtil.h"

//$PackageWebCoreBegin

//template<class T>
//QJsonValue IJsonUtil::_objectToJson(const QList<T>& sequence, bool &ok)
//{
//    QJsonArray array;
//    for(auto it = sequence.cbegin(); it != sequence.cend(); ++it){
//        array.append(_objectToJson(*it, ok));
//        if(!ok){
//            return {};
//        }
//    }
//    return array;
//}

//template<class T>
//QJsonValue IJsonUtil::_objectToJson(const QStack<T>& sequence, bool &ok)
//{
//    QJsonArray array;
//    for(auto it=sequence.cbegin(); it!=sequence.cend(); it++){
//        array.append(_objectToJson(*it, ok));
//        if(!ok){
//            return {};
//        }
//    }
//    return array;
//}

//template<class T>
//QJsonValue IJsonUtil::_objectToJson(const QQueue<T>& sequence, bool &ok)
//{
//    QJsonArray array;
//    for(auto it=sequence.cbegin(); it!=sequence.cend(); it++){
//        array.append(_objectToJson(*it, ok));
//        if(!ok){
//            return {};
//        }
//    }
//    return array;
//}

//template<class T>
//QJsonValue IJsonUtil::_objectToJson(const QVector<T>& sequence, bool &ok)
//{
//    QJsonArray array;
//    for(auto it=sequence.cbegin(); it!=sequence.cend(); it++){
//        array.append(_objectToJson(*it, ok));
//        if(!ok){
//            return {};
//        }
//    }
//    return array;
//}

//template<class T>
//QJsonValue IJsonUtil::_objectToJson(const std::list<T>& sequence, bool &ok)
//{
//    QJsonArray array;
//    for(auto it=sequence.cbegin(); it!=sequence.cend(); it++){
//        array.append(_objectToJson(*it, ok));
//        if(!ok){
//            return {};
//        }
//    }
//    return array;
//}

//template<class T>
//QJsonValue IJsonUtil::_objectToJson(const std::vector<T>& sequence, bool &ok)
//{
//    QJsonArray array;
//    for(auto it=sequence.cbegin(); it!=sequence.cend(); it++){
//        array.append(_objectToJson(*it, ok));
//        if(!ok){
//            return {};
//        }
//    }
//    return array;
//}

//template<class T, int N>
//QJsonValue IJsonUtil::_objectToJson(const std::array<T, N>& sequence, bool &ok)
//{
//    QJsonArray array;
//    for(auto it=sequence.cbegin(); it!=sequence.cend(); it++){
//        array.append(_objectToJson(*it, ok));
//        if(!ok){
//            return {};
//        }
//    }
//    return array;
//}

//template<class T>
//QJsonValue IJsonUtil::_objectToJson(const QMap<QString, T>& map, bool &ok)
//{
//    QJsonObject obj;
//    auto keys = map.keys();
//    for(auto key : keys){
//        obj[key] = _objectToJson(map[key], ok);
//        if(!ok){
//            return {};
//        }
//    }
//    return obj;
//}

//template<class T, class P>
//QJsonValue IJsonUtil::_objectToJson(const QPair<T, P> &pair, bool& ok)
//{
//    QJsonObject obj;
//    obj[IConvertUtil::toString(pair.first)] = _objectToJson(pair.second, ok);
//    if(!ok){
//        return {};
//    }
//    return obj;
//}

//template<class T>
//QJsonValue IJsonUtil::_objectToJson(const std::map<QString, T>& map, bool& ok)
//{
//    QJsonObject obj;
//    for(const auto& it : map){
//        obj[it.first] = _objectToJson<>(it.second, ok);
//        if(!ok){
//            return {};
//        }
//    }
//    return obj;
//}

//template <class T>
//typename std::enable_if<std::is_arithmetic<T>::value, QJsonValue>::type
//IJsonUtil::_objectToJson(const T& value, bool& ok)
//{
//    ok = true;
//    return value;
//}

//template<class T>
//typename std::enable_if<ITraitUtil::isBean<T>::value, QJsonValue>::type
//IJsonUtil::_objectToJson(const T& value, bool& ok)
//{
//    ok = true;
//    return value.toJson();
//}

//$PackageWebCoreEnd
