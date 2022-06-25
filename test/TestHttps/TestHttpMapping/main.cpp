#include <IWebCore>

$EnableBeanResolveStrictMode(true)
$EnableBluePrint(true)
int main(int argc, char *argv[])
{
    IApplication a(argc, argv);
    IHttpServer server;
    server.listen();


    return a.exec();
}
