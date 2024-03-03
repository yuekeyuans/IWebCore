#include <ICore/IApplication>
#include <ICore/IContext>
#include <IWeb/IWeb>

$EnableDefaultConfigFiles

$EnableTaskOutput(true)
$EnableControllerPrint(true)
$EnableCatagory(Controller)
$SetIpPort(1000)
$SetFileServiceMapping("D:/hello")

int main(int argc, char *argv[])
{
    IApplication a(argc, argv);

    IHttpServer server;
    server.listen();

    return a.exec();
}
