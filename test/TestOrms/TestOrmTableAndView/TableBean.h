#pragma once

#include <IWebCore>

class TableBean : public IOrmTableInterface<TableBean>
{
    Q_GADGET
    $AsTable(TableBean)
public:
    TableBean();

    $AutoGenerate(id)
    $PrimaryKey(id)
    $ColumnDeclare(qint64, id)
    int id = -1;
};

