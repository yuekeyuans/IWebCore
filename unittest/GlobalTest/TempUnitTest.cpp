#include "TempUnitTest.h"
#include "bean/StudentBean.h"

void TempUnitTest::test_IJson()
{
    qDebug() << __FUNCTION__;
}

void TempUnitTest::test_BeanList()
{
    QList<StudentBean> list;
    list.append(StudentBean{});
    list.append(StudentBean{});
    auto json = IJsonUtil::toJson(list);
    {
        auto id = IMetaUtil::registerMetaType<std::list<StudentBean>>().toList().first();
        auto ptr = new std::list<StudentBean>();

        qDebug() << IBeanTypeManage::instance()->getBeanFromJson(id)(ptr, json);
        auto obj = static_cast<std::list<StudentBean>*>(ptr);
        qDebug() << QString::fromStdString(IJsonUtil::toJson(*static_cast<std::list<StudentBean>*>(ptr)).dump());
    }
//    {
//        auto id = IMetaUtil::registerMetaType<StudentBeanQVector>();
//        auto ptr = QMetaType::create(id);
//        IBeanTypeManage::instance()->getBeanFromJson(id)(ptr, json);
//        auto obj = static_cast<StudentBeanQVector*>(ptr);
//        qDebug() << QString::fromStdString(obj->toJson().dump(4));
//    }
//    {
//        auto id = IMetaUtil::registerMetaType<StudentBeanStdList>();
//        auto ptr = QMetaType::create(id);
//        IBeanTypeManage::instance()->getBeanFromJson(id)(ptr, json);
//        auto obj = static_cast<StudentBeanStdList*>(ptr);
//        qDebug() << QString::fromStdString(obj->toJson().dump(4));
//    }
//    {
//        auto id = IMetaUtil::registerMetaType<StudentBeanStdVector>();
//        auto ptr = QMetaType::create(id);
//        IBeanTypeManage::instance()->getBeanFromJson(id)(ptr, json);
//        auto obj = static_cast<StudentBeanStdVector*>(ptr);
//        qDebug() << QString::fromStdString(obj->toJson().dump(4));
//    }
//    {
//        auto id = IMetaUtil::registerMetaType<QList<StudentBean>>();
//        qDebug() << id << QMetaType(id).typeName(id);
//        auto ptr = QMetaType::create(id);
//        IBeanTypeManage::instance()->getBeanFromJson(id)(ptr, json);
//        auto obj = static_cast<QList<StudentBean>*>(ptr);
//        qDebug() << QString::fromStdString(IJsonUtil::toJson(*obj).dump(4));
//    }
//    {
//        auto id = IMetaUtil::registerMetaType<std::list<StudentBean>>();
//        qDebug() << id << QMetaType(id).typeName(id);
//        auto ptr = QMetaType::create(id);
//        IBeanTypeManage::instance()->getBeanFromJson(id)(ptr, json);
//        auto obj = static_cast<std::list<StudentBean>*>(ptr);
//        qDebug() << QString::fromStdString(IJsonUtil::toJson(*obj).dump(4));
//    }
//    {
//        qDebug() << QMetaType::type("std::list<StudentBean>");
//        qDebug() << QMetaType::type("std::list<StudentBean, std::allocator<StudentBean> >");
//        qDebug() << QMetaType::type("QList<StudentBean>");
//        qDebug() << QMetaType::type("StudentBeanStdList");
    //    }
}

void TempUnitTest::test_RegisterTypeOutput()
{
//    for(int i=1024; i<3000; i++){
//        QString name = QMetaType::typeName(i);
//        if(!name.isEmpty()){
//            qDebug() << "type" << i << name;
//        }
//    }
}
