#include "ITestManage.h"

#include <QtTest>

ITestManage *ITestManage::instance(){
    static ITestManage inst;
    return & inst;
}

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
