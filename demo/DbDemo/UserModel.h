#pragma once

#include "orm/IOrmModelInterface.h"
#include "UserBean.h"

class UserModel : public IOrmModelInterface<UserBean>
{
public:
    UserModel();
};
