
#include <QtCore>

#include "orm/IOrmBase.h"
#include "orm/dialect/IOrmDialect.h"
#include "UserBean.h"
#include "UserModel.h"
#include <IWebCore>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    UserModel model;

    QList<UserBean> beans;

    for(int i=0; i<1; i++){
        UserBean bean;
        beans.append(bean);
    }
    $TIC
    model.insert(beans);
    $TAC

    qDebug() << beans.first().toJson() << endl;

    model.clearTable();

    qDebug() << model.count() << "count";
    return a.exec();
}
