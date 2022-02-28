#include <IWebCore>

#include <QtTest>

#include "TestTable.h"

int main(int argc, char *argv[])
{
    $ITestBegin;

    ITaskManage::run(argc, argv);

    $ITestClass(TestTable);

    $ITestEnd
}
