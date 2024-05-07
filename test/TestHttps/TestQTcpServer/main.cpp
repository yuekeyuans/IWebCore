#include <ICore/IApplication>
#include <ICore/IContext>

$EnableTaskOutput(true)
int main(int argc, char *argv[])
{
    IApplication app(argc, argv);


    return app.exec();
}
