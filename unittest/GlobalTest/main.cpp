#include <ICore/IApplication>
#include <ICore/IContext>
#include "tcp/ITcpServer.h"
#include "IHttpPythonTestAnnomacro.h"

$EnableTaskOutput(false)
$EnableUnitTest(false)
$EnableHttpPythonTest(true)
int main(int argc, char *argv[])
{
    IApplication app(argc, argv);
    ITcpServer server;
    server.listen();
    return app.run();
}
