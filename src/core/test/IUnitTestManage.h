#pragma once

#include "core/util/IHeaderUtil.h"
#include <core/unit/ISingletonUnit.h>
#include <QtTest>

$PackageWebCoreBegin

class IUnitTestManage : public ISingletonUnit<IUnitTestManage>
{
public:
    IUnitTestManage() = default;

public:
    void addTest(QObject* obj);
    void invokeTests();

private:
    QVector<QObject*> m_testCases;
};

inline void IUnitTestManage::addTest(QObject *obj)
{
    if(obj != nullptr){
        instance()->m_testCases.append(obj);
    }
}

inline void IUnitTestManage::invokeTests()
{
    auto& objs = instance()->m_testCases;
    for(auto obj : objs){
        QTest::qExec(obj);
    }
}
$PackageWebCoreEnd
