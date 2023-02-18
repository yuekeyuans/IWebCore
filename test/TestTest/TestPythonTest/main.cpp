#include <ICore/IApplication>
#include <ICore/ITest>

#include "python/IScriptUtil.h"

$EnableTaskOutput
$EnableCatagory(Test)

int main(int argc, char *argv[])
{
    qDebug() << "hello world";

    IApplication app(argc, argv);

    IScriptUtil::copyScript();
    IScriptUtil::execScript();


    return app.exec();
}
