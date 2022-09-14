#include <IWebCore>
#include "core/test/ITestManage.h"

int main(int argc, char *argv[])
{
    Q_UNUSED(argc)
    Q_UNUSED(argv)

    ITestManage::invokeAllTestClass();
}
