#include <IWebCore>


$EnableBeanResolveStrictMode(true)
//$EnableBluePrint(true)
int main(int argc, char *argv[])
{
    IWebApplication a(argc, argv);
    IHttpServer server;
    server.listen();
    return a.exec();
}
