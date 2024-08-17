#pragma once

#include "core/bean/IBeanInterface.h"
#include "NameBean.h"

class PersonBean : public IBeanInterface<PersonBean>
{
    Q_GADGET
public:
    PersonBean();

public:
    $BeanField(int, age, 10)
    $BeanField(NameBean, name1)
};

