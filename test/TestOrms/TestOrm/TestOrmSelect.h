#pragma once
#include <IWebCore>
#include <QtTest>
#include "PhoneBean.h"
#include "PhoneModel.h"

class TestOrmSelect : public ITestTaskInterface<TestOrmSelect>
{
    Q_OBJECT
    $AsTest(TestOrmSelect)
public:
    TestOrmSelect() = default;
    ~TestOrmSelect() = default;

private slots:
    //    void initTestCase();
    //    void cleanupTestCase();
    void init();
    //    void cleanup();
    void test_findOne();

    void test_findAll();

    void test_findAll1();

    void test_findOneByPk();

    void test_findColumns1();

    void test_findColumns2();

private:
    PhoneModel model;
};

