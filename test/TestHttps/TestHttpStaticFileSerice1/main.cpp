#include <QCoreApplication>

#include <IWebCore>

int main(int argc, char *argv[])
{
    IApplication app(argc, argv);
    IHttpServer server;
    server.serveStatic(R"(E:\project\cpp\IWeb\iweb2_doc\html)");
    server.listen();
    return app.exec();
}
