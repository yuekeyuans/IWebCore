#include <QCoreApplication>

#include <IWebCore>

int main(int argc, char *argv[])
{
    IApplication app(argc, argv);
    IHttpServer server;
    server.serveStatic(R"(E:\project\cpp\publish\IWebCore\src\core)");
    server.listen();
    return app.exec();
}
