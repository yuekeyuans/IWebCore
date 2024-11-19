#include <IWebCore>
#include <QtTest>

#include "TestConfig.h"
#include "TestFunctionCallConfiger.h"

$EnableCatagory(Test)
$EnableConfigFile("abc.tt");
int main(int argc, char *argv[])
{
    IApplication app(argc, argv);
    return app.exec();
}
