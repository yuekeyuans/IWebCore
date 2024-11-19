#pragma once

#include <IWebCore>

class UserBean : public IBeanInterface<UserBean>
{
    Q_GADGET
    $AsBean(UserBean)
public:
    UserBean();

    $BeanField(int, age);

    $BeanFieldDeclare(QString, name)
    QString name;


    $BeanFieldDeclare(QString, country)
    QString country = "CHINA";
};

