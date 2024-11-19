#include <IWebCore>

$EnableBluePrint (true)
int main(int argc, char *argv[])
{
    IApplication app(argc, argv);

    IHttpServer server;
    server.listen ();

    return app.exec ();
}
