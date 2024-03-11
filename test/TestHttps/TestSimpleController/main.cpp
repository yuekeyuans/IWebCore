#include <ICore/IApplication>
#include <ICore/IContext>
#include <IWeb/IWeb>

#pragma execution_character_set("utf-8")

$EnableDefaultConfigFiles
$EnableTaskOutput(true)
$SetIpPort(1000)
$EnableControllerPrint(true)
$EnableCatagory(Controller)
$SetFileServiceMapping("E:/123/export2/dest/倪柝声文集/")
//$SetFileServiceAttachmentSuffix("html", "htm", "rar")

int main(int argc, char *argv[])
{
    IApplication a(argc, argv);

    IHttpServer server;
    server.listen();

    return a.exec();
}
