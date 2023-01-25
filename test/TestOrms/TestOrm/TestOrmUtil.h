#pragma once

#include <IWebCore>
#include <QtTest>

class TestOrmUtil : public ITestTaskInterface<TestOrmUtil, false>
{
    Q_OBJECT
    $AsTest(TestOrmUtil)
public:
    TestOrmUtil();

private slots:
    void init();

};

