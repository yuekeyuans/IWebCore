#pragma once

#include <IWeb/IControllerInterface>
#include "TestBean.h"

class JsonReturnController : public IControllerInterface<JsonReturnController>
{
    Q_GADGET
    $AsController(JsonReturnController)
public:
    JsonReturnController();

    $GetMapping(getJson, json1)
    IJsonResponse getJson();

    $GetMapping(getJson2, json2)
    IJsonResponse getJson2();

    $GetMapping(getJson3, json3)
    QString getJson3();

    $GetMapping(getJson4, json4)
    IJsonResponse getJson4();

    $GetMapping(getJson5, json5)
    IJsonResponse getJson5();

    $GetMapping(getJson6, json6)
    IJsonResponse getJson6();

    $GetMapping(getJson7, json7)
    IJsonResponse getJson7();

    $GetMapping(getJson8, json8)
    QJsonArray getJson8();

    $GetMapping(getJson9, json9)
    QJsonObject getJson9();
};



