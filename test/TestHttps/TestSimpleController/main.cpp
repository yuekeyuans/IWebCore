#include <ICore/IApplication>
#include <ICore/IContext>
#include <IWeb/IWeb>

//#include "core/bean/IBeanTypeManage.h"


//class klassName : public ITaskInstantUnit < klassName, true >
//{
//public:
//    klassName() {
//        qDebug() << "Test";
//    }
//    virtual void task() final {
//        QString key = "SYSTEM_ENABLE_TASK_OUTPUT";
//        QJsonValue obj = QJsonValue(true);
//        IContextManage::instance()->addConfig(obj, key);
//    }
//};

$EnableTaskOutput
$EnableControllerPrint(true)
$EnableCatagory(Controller)
$SetIpPort(1000)

//class klassName : public IProfileTaskInterface < klassName, true >
//{
//public:
//                             klassName() = default;
//    virtual QJsonValue config() final   {  return 1000; }  \
//    virtual QString path() const final { return IToeUtil::trimQuote( "http.port" ); }  \
//};


int main(int argc, char *argv[])
{
    IApplication a(argc, argv);

//    IBeanTypeManage manage;

    IHttpServer server;
    server.setPort(81);
    server.listen();

    return a.exec();
}
