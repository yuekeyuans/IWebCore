#pragma once

#include <IWebCore>
#include "world/CountryTable.h"
#include "MySqlWorldDatabase.h"

class CountryModel : public IOrmTableModelInterface<CountryTable, MySqlWorldConnectionName>
{
public:
    CountryModel();
};

