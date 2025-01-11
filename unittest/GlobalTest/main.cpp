#include <ICore/IApplication>
#include <ICore/IContext>
//#include "tcp/ITcpServer.h"
#include "http/IHttpAnnomacro.h"
#include "http/IHttpServer.h"
#include "IHttpPythonTestAnnomacro.h"

$EnableTaskOutput(false)
$EnableUnitTest(false)
$EnableHttpPythonTest(true)

//$SetTcpResolverFactory("http")
//$SetTcpIp("127.0.0.1")
//$SetTcpPort(8999)

$SetHttpIp("127.0.0.1")
$SetHttpPort(8557)
int main(int argc, char *argv[])
{
    IApplication app(argc, argv);
    IHttpServer server;
    server.listen();
    return app.run();
}
