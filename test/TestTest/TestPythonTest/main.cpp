#include <ICore/IApplication>
#include <ICore/ITest>
#include <web/server/IHttpServer.h>

#include "python/IScriptUtil.h"

$EnableTaskOutput
$EnableCatagory(Test)

int main(int argc, char *argv[])
{
    qDebug() << "hello world";

    IApplication app(argc, argv);

    IScriptUtil::copyScript();
    IScriptUtil::execScript();

    IHttpServer server;
    server.listen();

    return app.exec();
}
