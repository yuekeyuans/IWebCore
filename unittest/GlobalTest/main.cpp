#include <ICore/IApplication>
#include <ICore/IContext>
//#include "tcp/ITcpServer.h"
#include "http/IHttpAnnomacro.h"
#include "http/IHttpServer.h"
#include "IHttpPythonTestAnnomacro.h"

#include "core/util/IMinidumpUtil.h"

#include <windows.h>
#include <dbghelp.h>
#include <tchar.h>
#include <iostream>

$EnableTaskOutput(false)
$EnableUnitTest(false)
$EnableHttpPythonTest(true)

//$SetTcpResolverFactory("http")
//$SetTcpIp("127.0.0.1")
//$SetTcpPort(8999)

$SetHttpIp("127.0.0.1")
$SetHttpPort(8561)
int main(int argc, char *argv[])
{


    IApplication app(argc, argv);
    IHttpServer server;
    server.listen();

    // 初始化崩溃捕获机制
    CrashHandler::Initialize();

    return app.run();
}
