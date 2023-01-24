#include <IWebCore>
#include <QtTest>

$EnableCatagory(Test)
$DisableTask(Test, TestGadget)

int main(int argc, char** argv){
    IApplication app(argc, argv);
    return app.exec();
}
