#include <IWebCore>
#include <QtTest>

$EnableCatagory(Test)
int main(int argc, char** argv){

    IApplication app(argc, argv);
    return app.exec();
}
