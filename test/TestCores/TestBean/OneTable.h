#pragma once

#include <IWebCore>

class OneTable : public IOrmTableInterface<OneTable>
{
    Q_GADGET
    $AsTable(OneTable)
public:
    OneTable();

    $AutoGenerate(id)
    $PrimaryKey(id)
    $Column(int, id)
};
