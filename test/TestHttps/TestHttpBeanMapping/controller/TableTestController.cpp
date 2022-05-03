#include "TableTestController.h"

TableTestController::TableTestController()
{

}

QString TableTestController::getTable($Param (UserTable, table))
{
    qDebug() << table_param;

    model.insert(table_param);

    return table_param;
}
