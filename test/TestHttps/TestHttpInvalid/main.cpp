//#include <ICore/IApplication>
#include <core/application/IAsioApplication.h>
#include <ICore/IContext>
//#include <IWeb/IHttpServer>
#include <http/net/IHttpServer.h>

$EnableTaskOutput(true)
int main(int argc, char *argv[])
{
    IAsioApplication a(argc, argv);

    IHttpServer server;
    server.listen();

    return a.run();
}
