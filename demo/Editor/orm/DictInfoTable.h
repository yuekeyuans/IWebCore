#pragma once

#include <IWebCore>

class DictInfoTable : public IOrmTableInterface
{
    Q_GADGET
    $AsTable(DictInfoTable)
public:
    DictInfoTable();


public:

    $AutoGenerate(id)
    $PrimaryKey(id)
    $Column(qint64, id)

    $Column(QString, name)
};

//$RegisterTable(DictInfoTable)
