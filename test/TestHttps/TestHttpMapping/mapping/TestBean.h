#pragma once

#include <IWebCore>

class TestBean : public IBeanInterface<TestBean>
{
    Q_GADGET
    $AsBean(TestBean)
public:
    TestBean();
    ~TestBean();

    $BeanFieldDeclare(QString, name);
    QString name = "yuekeyuan";

    $BeanFieldDeclare(int, age)
    int age = 100;
};

