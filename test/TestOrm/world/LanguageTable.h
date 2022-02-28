#pragma once

#include <IWebCore>

class LanguageTable : public IOrmTableInterface<LanguageTable>
{
    Q_GADGET
    $AsTable(LanguageTable)
public:
    LanguageTable();

    $Column(QString, CountryCode)
    $Column(QString, language)
    $Column(QString, IsOffical)
    $Column(QString, Percentage)
};
