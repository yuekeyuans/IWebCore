#include <IWebCore>

$EnableTaskOutput(true)

int main(int argc, char *argv[])
{
    IApplication a(argc, argv);

    return a.exec();
}
