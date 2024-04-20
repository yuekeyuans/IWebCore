#include <IWebCore>
#include <QtTest>

$EnableCatagory(Test)
//$EnableCatagory(StartUp)
//$EnableBluePrint()
//$EnableTaskOutput
//$DisableTest(TestGadget, TestTable)
//$EnableTest(TestGadget, TestTable)
int main(int argc, char** argv){
    IApplication app(argc, argv);
    return app.exec();
}
