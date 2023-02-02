#include <ICore/IApplication>
#include <IWeb/IHttpServer>

$DisableCatagory(Test)
int main(int argc, char *argv[])
{
    IApplication a(argc, argv);

    IHttpServer server;
    server.listen();

    return a.exec();
}
