#pragma once

#include <IWebCore>
#include "world/CountryTable.h"
#include "MySqlWorldDatabase.h"

extern const char SqliteConnectionName[];

class CountryModel : public IOrmTableModelInterface<CountryTable, SqliteConnectionName>
{
public:
    CountryModel();
};

