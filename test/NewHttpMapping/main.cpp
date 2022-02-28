#include <IWebCore>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    qDebug() << "hello world";

    qDebug() << QMetaType::type("IPlainTextResponse");

    for(int i=1024; i<1040; i++){
        qDebug() << QMetaType(i).typeName(i) << endl;
    }

    return a.exec();
}
