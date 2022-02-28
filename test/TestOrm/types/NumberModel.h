#pragma once

#include <IWebCore>
#include "NumberBean.h"
#include "SqliteDatabase.h"

class NumberModel : public IOrmTableModelInterface<NumberBean, SqliteConnectionName>
{

public:
    NumberModel();
};

