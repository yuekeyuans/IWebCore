#pragma once

#include <IWebCore>

class DataBean : public IOrmTableInterface<DataBean>
{
    Q_GADGET
    $AsTable(DataBean)
public:
    DataBean() = default;

    $AutoGenerate(id)
    $PrimaryKey(id)
    $Column(QString, id);

    $ColumnDeclare(QString, name);
    QString name = "hello world";
};

