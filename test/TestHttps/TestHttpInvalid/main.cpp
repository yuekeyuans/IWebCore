//#include <ICore/IApplication>
#include <core/application/IAsioApplication.h>
#include <ICore/IContext>
#include <http/net/server/IHttpServer.h>

$EnableTaskOutput(true)
int main(int argc, char *argv[])
{
    IAsioApplication a(argc, argv);

    IHttpServer server;
    server.listen();

    return a.run();
}
