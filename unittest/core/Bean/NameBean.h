#pragma once

#include "core/bean/IBeanInterface.h"

template<typename T>
using stdStringMap = std::map<std::string, T>;

class NameBean : public IBeanInterface<NameBean>
{
    Q_GADGET
public:
    NameBean();
    $BeanField(QString, name, "hello world")
    $BeanField(QStringList, value)
    $BeanField(QVector<int>, va1)
    $BeanField(stdStringMap<NameBean>, val2)
    $BeanField(QDate, date, QDate::currentDate())
};



