#pragma once

#include <IWebCore>

class ConditionBean : public IOrmTableInterface<ConditionBean>
{
    Q_GADGET
    $AsTable(ConditionBean)
public:
    ConditionBean();

    $AutoGenerate(id)
    $PrimaryKey(id)
    $Column(int, id)
};

