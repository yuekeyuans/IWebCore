#pragma once

#include "core/bean/IBeanInterface.h"
#include "JsonHeader.h"
#include "TestJson2.h"


class TestJson : public IBeanInterface<TestJson>
{
    Q_GADGET
public:
    TestJson();

    TO_JSON(int, intVal)

    TO_JSON(std::string, strVal)

    TO_JSON(std::vector<int>, vecInt)

    TO_JSON(TestJson2, jsonVal)

    TO_JSON(std::vector<TestJson2>, vecBean)

public:
    virtual IJson toJson(bool *ok) const;
    virtual bool loadJson(const IJson &value);
};

inline TestJson::TestJson()
{
    vecInt.push_back(12);
    vecInt.push_back(12123);
    vecBean.push_back({});
}

inline IJson TestJson::toJson(bool *ok) const
{
    IJson obj = IJson::object();
    obj["intVal"] = intVal_toJson();
    obj["strVal"] = strVal_toJson();
    obj["vecInt"] = vecInt_toJson();
    obj["jsonVal"] = jsonVal_toJson();
    obj["vecJson"] = vecBean_toJson();

    return obj;
}
