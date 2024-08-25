#pragma once

#include "core/bean/IBeanInterface.h"

class NameBean : public IBeanInterface<NameBean>
{
    Q_GADGET
public:
    NameBean() = default;
    $BeanField(QString, name, "hello world")
};

$AsBeanList(NameBean)


