#include <QtCore>
#include <IWebCore>
#include "plugins/Status404Page.h"

int main(int argc, char *argv[])
{   
    QCoreApplication a(argc, argv);
    IConfigurationInitializer configInit;
    IBase::registerStatuCodes(IHttpStatus::NOT_FOUND_404, Status404Page::instance());
    IControllerBase::instance()->travalPrintUrlTree();
    IHttpServer server;
    server.listen();
    return a.exec();
}
