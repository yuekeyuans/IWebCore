#include <ICore/IApplication>
#include <ICore/IContext>
#include <IWeb/IHttpServer>
#include "IHttpPythonTestAnnomacro.h"

#include "http/response/IJsonResponse.h"
#include "bean/StudentBean.h"

#include "core/util/IJsonUtil.h"

$EnableTaskOutput(true)
$EnableHttpPythonTest(true)
////$SetHttpPythonScriptDir(D:/test)
int main(int argc, char *argv[])
{
    IApplication app(argc, argv);
    IHttpServer server;
    server.listen();
    return app.run();
}
