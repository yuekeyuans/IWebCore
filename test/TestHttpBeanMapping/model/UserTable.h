#pragma once

#include <IWebCore>

class UserTable : public IOrmTableInterface<UserTable>
{
    Q_GADGET
    $AsTable(UserTable)
public:
    UserTable();

    $AutoGenerate(id)
    $PrimaryKey(id)
    $Column(qint64, id);

    $Column(QString, name);

    $Column(QDate, birthDate);
};

