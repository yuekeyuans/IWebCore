#include "TestFunctionCallConfiger.h"

void TestFunctionCallConfiger::test_1()
{
    qDebug() << connections();
    qDebug() << port();
    qDebug() << enabled();
    qDebug() << name();

    QTEST_ASSERT(connections() == 512);
    QTEST_ASSERT(port() == 230);
    QTEST_ASSERT(enabled() == true);
    QTEST_ASSERT(name() == "service 2");
}

void TestFunctionCallConfiger::test_SystemValue()
{
    auto value = IConfigurationManage::getStringValue("PP_FILE", nullptr, SystemConfigurationGroup);
    QTEST_ASSERT(value == "abc.tt");
}
