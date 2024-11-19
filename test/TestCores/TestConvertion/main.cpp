#include <QCoreApplication>

#include <IWebCore>
#include <QtTest>

$EnableCatagory(Test)
int main(int argc, char *argv[])
{
    Q_UNUSED(argc)
    Q_UNUSED(argv)
    IApplication app(argc, argv);
    return app.exec();
}
