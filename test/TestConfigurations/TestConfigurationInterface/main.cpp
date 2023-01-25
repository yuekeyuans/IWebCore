#include <IWebCore>

int main(int argc, char *argv[])
{
    IApplication a(argc, argv);

    bool ok;
    qDebug() << IConfigurationManage::getValue("name", &ok, ApplicationConfigurationGroup);

    return a.exec();
}
