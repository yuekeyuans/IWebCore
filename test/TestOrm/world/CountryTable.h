#pragma once

#include <IWebCore>

class CountryTable : public IOrmTableInterface<CountryTable>
{
    Q_GADGET
    $AsTable(CountryTable, country)
public:
    CountryTable() = default;
    ~CountryTable() = default;

    $PrimaryKey(Code)
    $Column(QString, Code)

    $Column(QString, Name)
    $Column(QString, Continent)
    $Column(QString, Region)
    $Column(double, SurfaceArea)
    $Column(int, IndepYear)
    $Column(int, Population)
    $Column(double, LifeExpectancy)
    $Column(double, GNP)
    $Column(double, GNPOld)
    $Column(QString, LocalName)
    $Column(QString, GovernmentForm)
    $Column(QString, HeadOfState)
    $Column(int, Capital)
    $Column(QString, Code2)
};


