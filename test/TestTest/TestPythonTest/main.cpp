#include <ICore/IApplication>
#include <ICore/ITest>

$EnableTaskOutput
//$EnableCatagory(Test)

int main(int argc, char *argv[])
{
    IApplication app(argc, argv);

    return app.exec();
}
