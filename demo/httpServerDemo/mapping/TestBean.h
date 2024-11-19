#pragma once

#include <QtCore>
#include <IWebCore>

class TestBean
{
    Q_GADGET
    $AsBean(TestBean)
public:
    TestBean();

    $BeanField(QString, name);

    $BeanField(int, age)
};

$RegisterBean(TestBean)
