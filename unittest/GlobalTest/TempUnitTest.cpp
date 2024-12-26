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
    auto json = list.toJson();
    {
        auto id = IMetaUtil::registerMetaType<StudentBeanQList>();
        auto ptr = QMetaType::create(id);
        IBeanTypeManage::instance()->getBeanAssign(id)(ptr, json);
        auto obj = static_cast<StudentBeanQList*>(ptr);
        qDebug() << QString::fromStdString(obj->toJson().dump(4));
    }
    {
        auto id = IMetaUtil::registerMetaType<StudentBeanQVector>();
        auto ptr = QMetaType::create(id);
        IBeanTypeManage::instance()->getBeanAssign(id)(ptr, json);
        auto obj = static_cast<StudentBeanQVector*>(ptr);
        qDebug() << QString::fromStdString(obj->toJson().dump(4));
    }
    {
        auto id = IMetaUtil::registerMetaType<StudentBeanStdList>();
        auto ptr = QMetaType::create(id);
        IBeanTypeManage::instance()->getBeanAssign(id)(ptr, json);
        auto obj = static_cast<StudentBeanStdList*>(ptr);
        qDebug() << QString::fromStdString(obj->toJson().dump(4));
    }
    {
        auto id = IMetaUtil::registerMetaType<StudentBeanStdVector>();
        auto ptr = QMetaType::create(id);
        IBeanTypeManage::instance()->getBeanAssign(id)(ptr, json);
        auto obj = static_cast<StudentBeanStdVector*>(ptr);
        qDebug() << QString::fromStdString(obj->toJson().dump(4));
    }
    {
        auto id = IMetaUtil::registerMetaType<QList<StudentBean>>();
        qDebug() << id << QMetaType(id).typeName(id);
        auto ptr = QMetaType::create(id);
        IBeanTypeManage::instance()->getBeanAssign(id)(ptr, json);
        auto obj = static_cast<QList<StudentBean>*>(ptr);
        qDebug() << QString::fromStdString(IJsonUtil::toJson(*obj).dump(4));
    }
}
