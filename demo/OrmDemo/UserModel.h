#pragma once

#include <IWebCore>
#include "UserTable.h"

class UserModel : public IOrmTableModelInterface<UserTable>
{
public:
    UserModel();
};

