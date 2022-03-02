#pragma once

#include <IWebCore>

class UserTable : public IOrmTableInterface<UserTable>
{
    Q_GADGET
    $AsTable(UserTable)
public:
    UserTable();


};

