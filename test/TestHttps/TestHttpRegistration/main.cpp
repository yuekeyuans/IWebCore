#include <IWebCore>
#include "HelloController.h"

int main(int argc, char *argv[])
{
    IApplication a(argc, argv);

    HelloController::instance()->unRegisterController();
    HelloController::instance()->registerController();

    IHttpServer server;
    server.listen();

    return a.exec();
}
