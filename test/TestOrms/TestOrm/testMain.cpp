#include <IWebCore>

int main(int argc, char** argv)
{
    ITaskManage::run(argc, argv);

    ITestManage::invokeAllTestClass();
}
