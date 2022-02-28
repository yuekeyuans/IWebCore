#pragma once

#include <IWebCore>
#include "DataBean.h"
#include "SqliteDb.h"

class SqliteModel : public IOrmTableModelInterface<DataBean, SqlLiteConnectionName>
{
public:
    SqliteModel();
};

