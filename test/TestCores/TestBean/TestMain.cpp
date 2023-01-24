#include <IWebCore>
#include <QtTest>

$EnableBluePrint(true)
$DisableCatagory(StartUp)
int main(int argc, char** argv){

    IApplication app(argc, argv);

    ITestManage::invokeAllTestClass();

    return app.exec();
}
