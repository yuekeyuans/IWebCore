#pragma once

#include <IWebCore>

class TestOrmPrimaryKey : public ITestTaskInterface<TestOrmPrimaryKey, false>
{
    Q_OBJECT
    $AsTest(TestOrmPrimaryKey)
public:
    TestOrmPrimaryKey();
    ~TestOrmPrimaryKey() = default;

private slots:
    void init();
};
