#pragma once

#include <QtTest>
#include <IWebCore>
#include "PhoneBean.h"
#include "PhoneModel.h"

class TestOrmCondition : public QObject
{
    Q_OBJECT

public:
    TestOrmCondition();
    ~TestOrmCondition();

private slots:
//    void initTestCase();
//    void cleanupTestCase();
//    void init();
//    void cleanup();
    void test_and();
    void test_and1();

    void test_not();
    void test_not1();
    void test_not2();
    void test_not3();
    void test_condition1();
    void test_condition2();
    void test_condition3();
    void test_condition4();

    void test_or();

    void test_like();
    void test_unlike();
    void test_startWith();
    void test_endWith();
    void test_contain();

    void test_multiCondition();

private:
    bool isMatch(QString str, QString pattern);

};
