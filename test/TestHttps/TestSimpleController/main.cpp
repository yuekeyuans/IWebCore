#include <ICore/IApplication>
#include <IWeb/IWeb>

$EnableTaskOutput
int main(int argc, char *argv[])
{
    IApplication a(argc, argv);

    IHttpServer server;
    server.setPort(81);
    server.listen();

    return a.exec();
}
