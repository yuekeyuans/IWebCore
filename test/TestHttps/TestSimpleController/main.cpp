#include <ICore/IApplication>
#include <ICore/IContext>
#include <IWeb/IWeb>

#include "core/bean/IBeanTypeManage.h"

$EnableTaskOutput
$EnableControllerPrint(true)
$EnableCatagory(Controller)

$SetIpPort(1000)
int main(int argc, char *argv[])
{
    IApplication a(argc, argv);

    IHttpServer server;
    server.setPort(81);
    server.listen();

    return a.exec();
}
