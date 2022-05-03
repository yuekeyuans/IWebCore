
#include <IWebCore>

$EnableBluePrint(false)
int main(int argc, char *argv[])
{
    IWebApplication app(argc, argv);

    IHttpServer server;
    server.listen();

    return app.exec();
}
