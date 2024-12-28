#include <ICore/IApplication>
#include <ICore/IContext>
#include <IWeb/IHttpServer>
#include "IHttpPythonTestAnnomacro.h"

$EnableTaskOutput(false)
$EnableUnitTest(false)
$EnableHttpPythonTest(true)
int main(int argc, char *argv[])
{
    IApplication app(argc, argv);
    IHttpServer server;
    server.listen();
    return app.run();
}
