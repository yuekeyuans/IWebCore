#pragma once

#include "core/bean/IBeanInterface.h"
#include "core/util/IJsonUtil.h"

using namespace IWebCore;

class StudentBean : public IBeanInterface<StudentBean>
{
    Q_GADGET
public:
    StudentBean();

    $BeanField(int, index, 100)
    $BeanField(QString, name, "yuekeyuan")
};
