#pragma once

#include "core/bean/IBeanInterface.h"
#include "core/util/IJsonUtil.h"

using namespace IWebCore;

class StudentBean : public IBeanInterface<StudentBean>
{
    Q_GADGET
public:
    StudentBean();
    StudentBean(int id, QString name){
        this->index = id;
        this->name = name;
    }

    $BeanField(int, index, 100)
    $BeanField(QString, name, "yuekeyuan")
};
