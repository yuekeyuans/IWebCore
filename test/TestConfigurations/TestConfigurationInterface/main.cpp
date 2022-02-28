#include <IWebCore>

int main(int argc, char *argv[])
{
//    QCoreApplication a(argc, argv);

    ITaskManage::run(argc, argv);

    bool ok;
    qDebug() << IConfigurationManage::getValue("name", &ok, ApplicationConfigurationGroup);

//    return a.exec();
}
