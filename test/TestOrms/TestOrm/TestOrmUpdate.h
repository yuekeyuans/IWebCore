#pragma once
#include <IWebCore>
#include <QtTest>
#include "PhoneBean.h"
#include "PhoneModel.h"

class TestOrmUpdate : public ITestTaskInterface<TestOrmUpdate>
{
    Q_OBJECT
    $AsTest(TestOrmUpdate)
public:
    TestOrmUpdate();
    ~TestOrmUpdate() = default;

private slots:
    void init();
    void test_updateBean();
    void test_updateBeans();
    void test_updateBeansColumns();
    void test_updateByColumns();
    void test_updateByCondition();
    void test_updateBeanColumns();
private:
    PhoneModel  model;
};

