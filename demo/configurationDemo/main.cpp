#include <QCoreApplication>

#include <QtCore>
#include <IWebCore>

#include "DemoBeanGlobalConfig.h"
#include "DemoBeanGoupConfig.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    IConfigurationInitializer initializer;
    DemoBeanGlobalConfig bean1;
    qDebug() << bean1.name << bean1.age;

    DemoBeanGoupConfig bean2;
    qDebug() << bean2.name << bean2.age;

    return a.exec();
}
