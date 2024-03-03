#include <ICore/IApplication>
#include <ICore/IContext>
#include <IWeb/IWeb>


$EnableTaskOutput(true)
$SetIpPort(1000)
$EnableDefaultConfigFiles
$EnableControllerPrint(true)
$EnableCatagory(Controller)
$SetFileServiceMapping("E:/123/export2/dest/倪柝声文集/")

int main(int argc, char *argv[])
{
    IApplication a(argc, argv);

    IHttpServer server;
    server.listen();

    return a.exec();
}
