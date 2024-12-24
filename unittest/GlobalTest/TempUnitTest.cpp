#include "TempUnitTest.h"
#include "bean/StudentBean.h"

void TempUnitTest::test_IJson()
{
    qDebug() << __FUNCTION__;
}

void TempUnitTest::test_BeanList()
{
    StudentBeanQList list;
    list.append(StudentBean{});
    list.append(StudentBean{});

    qDebug() << __FUNCTION__;
    std::cout << list.toJson();
//    std::cout << list.toJson().dump();
}
