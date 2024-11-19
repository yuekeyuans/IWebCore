#include "TestGadget.h"
#include "core/bean/IBeanTypeManage.h"

#include "OneBean.h"

void TestGadget::init()
{
}

void TestGadget::test_Registration()
{
    QStringList names;
    for(int i=1025; ; i++){
        QString name = QMetaType(i).typeName(i);
        if(name.isEmpty()){
            break;
        }
        names.append(name);
    }
    QTEST_ASSERT(names.contains("OneBean"));
    QTEST_ASSERT(names.contains("OneBean&"));
}

void TestGadget::test_typeManageRegistration()
{
    QTEST_ASSERT(IBeanTypeManage::containBean("OneBean"));
}

void TestGadget::test_method()
{
    OneBean bean;
    qDebug() << bean.toJson();
    qDebug() << (QString) bean;
    bean.name = "hello world";
    OneBean bean1 = std::move(bean);
    QTEST_ASSERT(bean1.name == "hello world");

    qDebug() << "bean1" << bean1;
    qDebug() << "bean " <<  bean;
}

void TestGadget::test_className()
{
   OneBean bean;
   auto name = bean.className();
   QTEST_ASSERT(name == "OneBean");
}

void TestGadget::test_clone()
{
    OneBean bean;
    bean.id = 1;
    bean.name = "oo";
    OneBean bean1 = bean.clone();
    QTEST_ASSERT(bean == bean1);
}

void TestGadget::test_Initialized()
{
    OneBean bean;
    qDebug() << bean.id;
    QTEST_ASSERT(bean.id == 0);
}
