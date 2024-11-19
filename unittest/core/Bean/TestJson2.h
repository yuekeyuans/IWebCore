#pragma once
#pragma once

#include "core/bean/IBeanInterface.h"
#include "core/util/ITraitUtil.h"
#include "JsonHeader.h"


class TestJson2 : public IBeanInterface<TestJson2>
{
    Q_GADGET
public:
    TestJson2();

    TO_JSON(int, intVal)

    TO_JSON(std::string, strVal)

    TO_JSON(std::vector<int>, vecInt)

public:
    virtual IJson toJson(bool *ok) const;
};

inline TestJson2::TestJson2()
{

    vecInt.push_back(12);
    vecInt.push_back(12123);
}

inline IJson TestJson2::toJson(bool *ok) const
{
    IJson obj = IJson::object();
    obj["intVal"] = intVal_toJson();
    obj["strVal"] = strVal_toJson();
    obj["vecInt"] = vecInt_toJson();

    return obj;
}
