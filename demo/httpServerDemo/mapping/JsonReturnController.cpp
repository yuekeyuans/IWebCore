#include "JsonReturnController.h"

#include "base/IJsonUtil_tojson.h"

JsonReturnController::JsonReturnController()
{
    $ConstructController
}

IJsonResponse JsonReturnController::getJson()
{
    QJsonArray array;
    array.append("hello");
    array.append("world");
    return array;
}

IJsonResponse JsonReturnController::getJson2()
{
    return "{\"hello\" : \"world\" }"_json;
}

QString JsonReturnController::getJson3()
{
    return "$json:{\"hello\" : \"world\"}";
}

IJsonResponse JsonReturnController::getJson4()
{
    TestBean bean;
    return {bean};
}

// TODO: bean 设计好了，但是这里是有一些问题的。
IJsonResponse JsonReturnController::getJson5()
{
    QList<QMap<QString, TestBean>> beans;
    beans.append({{"hello", TestBean{}}});
    beans.append({{"hello", TestBean{}}});
    return IJsonUtil::objectToString(beans);
}

IJsonResponse JsonReturnController::getJson6()
{
    QMap<QString, QString> names;
    names.insert("hello", "world");
    return IJsonUtil::objectToString(names);
}

IJsonResponse JsonReturnController::getJson7()
{
    QList<QString> list;
    list << "hello" << "world";
    return IJsonUtil::objectToString(list);
}

QJsonArray JsonReturnController::getJson8()
{
    QJsonArray array;
    array.append("hello");
    array.append("world");
    return array;
}

QJsonObject JsonReturnController::getJson9()
{
    QJsonObject obj;
    obj["hello"] = "world";
    return obj;
}
