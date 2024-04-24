#include <ICore/IApplication>
#include <ICore/IContext>
#include <IWeb/IHttpServer>

$EnableTaskOutput(true)
int main(int argc, char *argv[])
{
    IApplication a(argc, argv);

    IHttpServer server;
    server.listen();

    return a.exec();
}
