#pragma once

#include <IWebCore>

class PhoneBean : public IOrmTableInterface<PhoneBean>
{
    Q_GADGET
    $AsTable(PhoneBean)
public:
    PhoneBean();

    $AutoGenerate(id)
    $NotNull(id)
    $PrimaryKey(id)
    $Column(qint64, id)

    $ColumnDeclare(QString, name)
    QString name = "yuekeyuan";

    $Column(QString, phoneNumber);
};

