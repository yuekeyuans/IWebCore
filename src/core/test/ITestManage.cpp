#include "ITestManage.h"

#include <QtTest>

void ITestManage::registerTestClass(QObject *obj)
{
    if(obj != nullptr){
        instance()->m_objs.append(obj);
    }
}

void ITestManage::invokeAllTestClass()
{
    auto& objs = instance()->m_objs;
    for(auto obj : objs){
        QTest::qExec(obj);
    }
}
