#pragma once

#include <IWebCore>
#include <QtTest>

class TestConfig : public ITestTaskInterface<TestConfig>
{
    Q_OBJECT
    $AsTest(TestConfig)
public:
    TestConfig();

private slots:
    void init();
    void test1();

};

