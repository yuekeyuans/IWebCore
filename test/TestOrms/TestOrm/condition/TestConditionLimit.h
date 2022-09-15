#pragma once

#include <QtTest>
#include <IWebCore>

class TestConditionLimit : public ITestInterface<TestConditionLimit>
{
    Q_OBJECT
    $AsTest(TestConditionLimit)
public:
    TestConditionLimit();

private slots:
    void init();
};

