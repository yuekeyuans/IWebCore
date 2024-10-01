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

//    TO_JSON(TestJson2, jsonVal)

    TestJson2 name;
    Q_INVOKABLE IJson jsonVal_toJson () const
    {
        if constexpr (std::is_arithmetic_v< TestJson2 >){
            return WrapPlainType(name);
        } else if constexpr (std::is_same_v<std::string, TestJson2 >){
            return WrapPlainType(name);
        }  else if constexpr (ITraitUtil::is_std_vector_v< TestJson2 >){
            return WrapProcessWith< TestJson2 >( name );
        }  else if constexpr ($HAS_CLASS_MEMBER_toJson< TestJson2 >::value){
            return WrapBeanType(name);
        }
        return nullptr;
    }

public:
    virtual IJson toJson(bool *ok) const;
    virtual bool loadJson(const IJson &value);
};

inline TestJson::TestJson()
{
    vecInt.push_back(12);
    vecInt.push_back(12123);
}



inline IJson TestJson::toJson(bool *ok) const
{
    IJson obj = IJson::object();
    obj["intVal"] = intVal_toJson();
    obj["strVal"] = strVal_toJson();
    obj["vecInt"] = vecInt_toJson();
    obj["jsonVal"] = jsonVal_toJson();

    return obj;
}
