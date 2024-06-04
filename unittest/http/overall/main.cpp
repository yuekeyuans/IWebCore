#include <ICore/IApplication>
#include <ICore/IContext>
#include <http/net/server/IHttpServer.h>

$EnableTaskOutput(true)
int main(int argc, char *argv[])
{
    IAsioApplication app(argc, argv);

    IHttpServer server;
    server.listen();

    return app.run();
}
