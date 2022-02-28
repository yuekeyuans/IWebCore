#pragma once

#include <IWebCore>
#include "world/CityTable.h"
#include "MySqlWorldDatabase.h"

class CityModel : public IOrmTableModelInterface<CityTable, MySqlWorldConnectionName>
{
    Q_GADGET
public:
    CityModel();
};
