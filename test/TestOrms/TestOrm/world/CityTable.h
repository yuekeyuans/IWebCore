#pragma once

#include <IWebCore>

class CityTable : public IOrmTableInterface<CityTable>
{
    Q_GADGET
    $AsTable(CityTable, city)
public:
    CityTable();

    $AutoGenerate(ID)
    $PrimaryKey(ID)
    $Column(int, ID)

    $Column(QString, Name);

    $Column(QString, CountryCode)

    $Column(QString, District)

    $Column(int, Population)
};

