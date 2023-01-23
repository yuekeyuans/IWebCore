#include <IWebCore>
#include <QtTest>

int main(int argc, char** argv){

    IApplication app(argc, argv);


    ITestManage::invokeAllTestClass();

    return app.exec();
}
