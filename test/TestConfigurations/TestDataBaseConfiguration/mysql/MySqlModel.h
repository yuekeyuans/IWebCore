#pragma once

#include <IWebCore>
#include "DataBean.h"
#include "MySqlDb.h"

class MySqlModel : public IOrmTableModelInterface<DataBean, MySqlDbConnection>
{
public:
    MySqlModel();
};

