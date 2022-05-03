#include <IWebCore>

#include <QtTest>

#include "TestTable.h"
#include "TestView.h"

int main(int argc, char *argv[])
{
    $ITestBegin;

    ITaskManage::run(argc, argv);

    $ITestClass(TestTable);
    $ITestClass(TestView)

    $ITestEnd
}
