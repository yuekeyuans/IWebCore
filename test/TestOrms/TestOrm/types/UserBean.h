#pragma once

#include <IWebCore>

class UserBean : public IOrmTableInterface<UserBean>
{
    Q_GADGET
    $AsTable(UserBean)
public:
    UserBean() = default;

    $AutoGenerate(id)
    $PrimaryKey(id)
    $Column(QString, id)

    $Column(bool, isMarried);

    $Column(QDate, birthDate);

    $Column(QTime, wakeTime);

    $Column(QDateTime, lastLoginTime)

    $SqlType(name, TEXT)
    $Column(QString, name)
};


