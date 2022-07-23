#include <IWebCore>

$EnableBeanResolveStrictMode(true)
$EnableBluePrint(true)
$EnableDefaultStaticDir("C:/ProgramData/Microsoft/Windows/OneSettings/")

int main(int argc, char *argv[])
{
    IApplication a(argc, argv);
    IHttpServer server;
//    server.setDefaultStaticDir(R"(C:\ProgramData\Microsoft\Windows\OneSettings\)");

    server.get("/functionGet", [](const IRequest&, IResponse&){
        // to do something;
    });


    server.listen();

    return a.exec();
}
