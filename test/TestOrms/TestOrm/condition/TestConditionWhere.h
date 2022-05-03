#pragma once

#include <QtTest>
#include <IWebCore>
#include "world/CityTable.h"
#include "world/CityModel.h"

#include "world/CountryModel.h"

class TestConditionWhere : public QObject
{
    Q_OBJECT
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
