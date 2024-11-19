#pragma once

#include <IWebCore>
#include <QtTest>

class TestConditionOrderBy : public ITestTaskInterface<TestConditionOrderBy>
{
    Q_OBJECT
    $AsTest(TestConditionOrderBy)
public:
    TestConditionOrderBy();

private slots:
    void test1();

};

