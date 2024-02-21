#include <ICore/IApplication>
#include <ICore/IContext>
#include <IWeb/IWeb>


$EnableTaskOutput
$EnableBluePrint(true)
$EnableCatagory(Controller)
int main(int argc, char *argv[])
{
    IApplication a(argc, argv);

    IHttpServer server;
    server.setPort(81);
    server.listen();

    return a.exec();
}
