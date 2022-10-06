#include <IWebCore>

$EnableBluePrint(true)
int main(int argc, char *argv[])
{
    IApplication app(argc, argv);

    IHttpServer server;
    server.listen();

    ITestManage::invokeAllTestClass();
    return app.exec();

}
