#include <ICore/IApplication>
#include <ICore/IContext>
#include <IWeb/IHttpServer>
#include "IHttpPythonTestAnnomacro.h"

#include "http/response/IJsonResponse.h"
#include "core/util/IJsonUtil.h"

$EnableTaskOutput(true)
$EnableUnitTest(false)
$EnableHttpPythonTest(true)
int main(int argc, char *argv[])
{
    IApplication app(argc, argv);
    IHttpServer server;
    server.listen();
    return app.run();
}
