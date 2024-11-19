#include "IWebCore"
#include <QtTest>
#include "TestConfig.h"
#include "core/application/IApplicationPreProcessor.h"

$EnableCatagory(Test)
int main(int argc, char *argv[])
{
    IApplication app(argc, argv);
    return app.exec();
}
