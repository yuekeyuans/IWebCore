#include <IApplication>

$DisableCatagory(StartUp)
int main(int argc, char *argv[])
{
    IApplication a(argc, argv);

    return a.exec();
}
