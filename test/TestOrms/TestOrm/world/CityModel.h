#pragma once

#include <IWebCore>
#include "world/CityTable.h"
#include "MySqlWorldDatabase.h"

extern const char SqliteConnectionName[];

class CityModel : public IOrmTableModelInterface<CityTable, SqliteConnectionName>
{
    Q_GADGET
public:
    CityModel();
};
