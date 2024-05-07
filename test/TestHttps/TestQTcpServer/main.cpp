#include <ICore/IApplication>
#include <ICore/IContext>

#include "lib/QHttpServer.h"

$EnableTaskOutput(true)
int main(int argc, char *argv[])
{
    IApplication app(argc, argv);

    QHttpServer server;
    server.listen();

    return app.exec();
}
