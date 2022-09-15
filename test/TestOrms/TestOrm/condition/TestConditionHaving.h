#pragma once

#include <QtTest>
#include <IWebCore>

class TestConditionHaving : public ITestInterface<TestConditionHaving>
{
    Q_OBJECT
    $AsTest(TestConditionHaving)
public:
    TestConditionHaving();

private slots:
    void init();
};

