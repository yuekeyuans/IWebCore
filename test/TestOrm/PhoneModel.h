#pragma once
#include <IWebCore>
#include "PhoneBean.h"
#include "SqliteDatabase.h"

class PhoneModel : public IOrmTableModelInterface<PhoneBean, SqliteConnectionName>
{
public:
    PhoneModel();
};

