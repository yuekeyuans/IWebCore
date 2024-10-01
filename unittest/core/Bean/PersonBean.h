#pragma once

#include "core/bean/IBeanInterface.h"
#include "NameBean.h"
#include "IJson.h"

class PersonBean : public IBeanInterface<PersonBean>
{
    Q_GADGET
public:
    PersonBean();
public:
    $BeanField(int, age, 10)

    $BeanField(NameBean, name1)
    $BeanField(ushort, gender, 1)
    $BeanField(std::string, friendName, "yuekeyuan")
//    $BeanField(NameBeanList, name2)
};

//$AsBeanList(PersonBean)
