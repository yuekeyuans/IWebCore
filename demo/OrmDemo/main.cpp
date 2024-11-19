#include <IWebCore>

#include "UserTable.h"
#include "UserModel.h"

$EnableSqlInfoPrint(false)
int main(int argc, char *argv[])
{
    IWebApplication app(argc, argv);

    UserModel model;

    UserTable table1;
    table1.name = "yuekeyuan";
    model.insert(table1);
    qDebug().noquote() << table1;

    UserTable table2;
    table2.name = "zhiyongfei";
    model.insert(table2);
    qDebug().noquote() << table2;

    qDebug() << model.count();
    qDebug().noquote() << IConvertUtil::toString(model.findAll());

    model.deleted(table1);
    qDebug().noquote() << model.count();
    qDebug().noquote() << IConvertUtil::toString(model.findAll());

    return app.exec();
}
