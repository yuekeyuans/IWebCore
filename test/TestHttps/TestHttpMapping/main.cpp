#include <IWebCore>
#include "core/config/IConfigAnnomacro.h"

//$EnableBeanResolveStrictMode(true)
//$EnableBluePrint(true)
//$EnableDefaultStaticDir("C:/ProgramData/Microsoft/Windows/OneSettings/")
$EnableTaskOutput(true)

int main(int argc, char *argv[])
{
    IApplication a(argc, argv);
    IHttpServer server;
//    server.setDefaultStaticDir(R"(C:\ProgramData\Microsoft\Windows\OneSettings\)");

    server.get("functionGet", [](const IRequest& req, IResponse& resp){
        Q_UNUSED(req)
        resp.setStatus(IHttpStatus::OK_200);
//        resp.setMime(IHttpMime::TEXT_HTML_UTF8);
        resp.setContent("hello world");
    });

    IControllerManage::travalPrintUrlTree();

    server.listen();

    return a.exec();
}
