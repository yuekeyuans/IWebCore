#pragma once

#include <IWebCore>
#include "PhoneBean.h"
#include "MysqlDatabase.h"

class SqliteModel : public IOrmTableModelInterface<PhoneBean, MySqlDatabaseConnectionName>
{
public:
    SqliteModel();
};
