#pragma once

#include <IWebCore>
#include "model/UserModel.h"
#include "model/UserTable.h"

class TableTestController : public IControllerInterface<TableTestController>
{
    Q_GADGET
    $AsController(TableTestController, tableController)
public:
    TableTestController();

    $GetMapping(getTable, getTable)
    QString getTable($Param(UserTable, table));

private:
    UserModel model;
};

