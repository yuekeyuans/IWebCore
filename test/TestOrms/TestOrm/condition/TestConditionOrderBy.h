#pragma once

#include <IWebCore>
#include <QtTest>

class TestConditionOrderBy : public ITestInterface<TestConditionOrderBy>
{
    Q_OBJECT
    $AsTest(TestConditionOrderBy)
public:
    TestConditionOrderBy();

private slots:
    void test1();

};

