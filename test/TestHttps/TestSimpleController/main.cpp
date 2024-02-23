#include <ICore/IApplication>
#include <ICore/IContext>
#include <IWeb/IWeb>

//#include "core/bean/IBeanTypeManage.h"


class klassName : public ITaskInstantUnit < klassName, true >
{
public:
    klassName() = default;
    virtual void task() final {
        QString key = "hello";
        QJsonValue obj = QJsonValue(true);
        IContextManage::instance()->addConfig(obj, key);
    }
};

$EnableTaskOutput
$EnableControllerPrint(true)
$EnableCatagory(Controller)
$SetIpPort(1000)
int main(int argc, char *argv[])
{
    IApplication a(argc, argv);

//    IBeanTypeManage manage;

    IHttpServer server;
    server.setPort(81);
    server.listen();

    return a.exec();
}
