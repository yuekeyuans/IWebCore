#include "FirstTest.h"
#include "TestController.h"
#include <QtTest>

UnitTest::UnitTest()
{
}

void UnitTest::slotTest()
{
    auto value = TestController::instance()->test();
    QVERIFY(value == "hello world");
}
