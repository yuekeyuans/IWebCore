#pragma once

#include <IWebCore>
#include "UserBean.h"

#include "SqliteDatabase.h"

class UserModel : public IOrmTableModelInterface<UserBean, SqliteConnectionName>
{
public:
    UserModel();
};

