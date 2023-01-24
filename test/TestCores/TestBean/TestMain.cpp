#include <IWebCore>
#include <QtTest>

$EnableCatagory(Test)
$DisableTest(TestGadget, TestTable)
int main(int argc, char** argv){
    IApplication app(argc, argv);
    return app.exec();
}
