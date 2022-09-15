#pragma once

#include <QtTest>
#include <IWebCore>
#include "world/CityTable.h"
#include "world/CityModel.h"

#include "world/CountryModel.h"

class TestConditionWhere : public ITestInterface<TestConditionWhere>
{
    Q_OBJECT
    $AsTest(TestConditionWhere)
public:
    TestConditionWhere();

private slots:
    void init();
    void test_length();
    void test_where1();


private:
    CityModel cityModel;
    CountryModel countryModel;
};
