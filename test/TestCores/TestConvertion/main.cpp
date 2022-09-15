#include <QCoreApplication>

#include <IWebCore>
#include <QtTest>

int main(int argc, char *argv[])
{
    Q_UNUSED(argc)
    Q_UNUSED(argv)
    ITestManage::invokeAllTestClass();
}
