#include <ICore/IApplication>
#include <IWeb/IWeb>
#include "core/config/IConfigAnnomacro.h"

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
