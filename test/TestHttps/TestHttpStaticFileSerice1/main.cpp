#include <QCoreApplication>

#include <IWebCore>

int main(int argc, char *argv[])
{
    IApplication app(argc, argv);
    IHttpServer server;
    server.listen();
    app.exe()
}
