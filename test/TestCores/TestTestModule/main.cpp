#include "ICore/IApplication"
#include "IWeb/IHttpServer"
#include "core/config/IConfigAnnomacro.h"

$EnableTaskOutput(true)

int main(int argc, char *argv[])
{
    IApplication app(argc, argv);

    IHttpServer server;
    server.listen();


    return app.exec();
}
