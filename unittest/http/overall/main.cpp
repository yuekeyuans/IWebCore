#include <ICore/IApplication>
#include <ICore/IContext>
#include <http/server/IHttpServer.h>

$EnableTaskOutput(true)
//$DisableCatagory(Test)
int main(int argc, char *argv[])
{
    IAsioApplication app(argc, argv);

    IHttpServer server;
    server.listen();

    return app.run();
}
