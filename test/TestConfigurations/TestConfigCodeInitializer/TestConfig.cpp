#include "TestConfig.h"
#include "ConfigBean.h"

TestConfig::TestConfig()
{

}

void TestConfig::init(){

}

void TestConfig::test1()
{
    ConfigBean bean;
    qDebug() << bean.age << bean.name;
    QTEST_ASSERT(bean.age == 102);
    QTEST_ASSERT(bean.name == "zhi");
}
