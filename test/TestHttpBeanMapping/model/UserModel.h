#pragma once

#include <IWebCore>
#include "model/UserTable.h"

class UserModel : public IOrmTableModelInterface<UserTable>
{
public:
    UserModel();
};

