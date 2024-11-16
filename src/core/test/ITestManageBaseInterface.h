#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/unit/ISingletonUnit.h"
#include <QtTest>

$PackageWebCoreBegin

template<typename T>
class ITestManageBaseInterface : public ISingletonUnit<T>
{
public:
    ITestManageBaseInterface() = default;

public:
    void addTest(QObject* obj);
    void invokeTests();

private:
    QVector<QObject*> m_testCases;
};

template<typename T>
void ITestManageBaseInterface<T>::addTest(QObject *obj)
{
    if(obj != nullptr){
        instance()->m_testCases.append(obj);
    }
}

template<typename T>
void ITestManageBaseInterface<T>::invokeTests()
{
    auto& objs = instance()->m_testCases;
    for(auto obj : objs){
        QTest::qExec(obj);
    }
}

$PackageWebCoreEnd
