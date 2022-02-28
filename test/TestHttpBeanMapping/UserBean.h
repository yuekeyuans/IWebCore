#pragma once

#include <IWebCore>

class UserBean : public IBeanInterface<UserBean>
{
    Q_GADGET
    $AsBean(UserBean)
public:
    UserBean();

    $FieldIgnorable(id)
    $BeanField(qint64, id);

    $BeanField(QString, name);

    $BeanField(QString, home);
    $BeanField(int, age);
    $BeanField(QDate, birthDate);

};

