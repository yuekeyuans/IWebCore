#include <QtCore>
#include <IWebCore.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    qDebug() << "start";

    IControllerBase::instance()->travalPrintUrlTree();

    return a.exec();
}
