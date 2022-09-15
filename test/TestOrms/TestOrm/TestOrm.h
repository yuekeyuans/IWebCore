#pragma once

#include <IWebCore>
#include <QtTest>
#include "PhoneModel.h"

class TestOrm : public ITestInterface<TestOrm>
{
    Q_OBJECT
    $AsTest(TestOrm)
public:
    TestOrm();
    ~TestOrm();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void init();
    void cleanup();
    void test_count();
    void test_insert();
    void test_insertId();
    void test_insertMuch();

    // delete
    void test_deleteById();
    void test_deleteCondition();
    void test_deleteBean();
    void test_deleteBeans();
    void test_deleteSql();

    // update
    void test_updateBean();


    // count
    void test_count1();
    void test_count2();

private:
    PhoneModel model;
};
