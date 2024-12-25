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

    std::cout << list.toJson();

    auto json = list.toJson();

    auto id = IMetaUtil::registerMetaType<StudentBeanQList>();
    qDebug() << id << QMetaType::typeName(id);

    auto ptr = QMetaType::create(id);

    IBeanTypeManage::instance()->getBeanAssign(id)(ptr, json);

    auto obj = static_cast<StudentBeanQList*>(ptr);
    qDebug() << obj->length();
}
