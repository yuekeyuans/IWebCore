#pragma once

#include "core/bean/IBeanInterface.h"

class NameBean : public IBeanInterface<NameBean>
{
    Q_GADGET
    $AsBean
public:

public:
    NameBean();
    $BeanField(QString, name, "hello world")
};

