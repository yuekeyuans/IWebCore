#pragma once

#include <IWebCore>

class TestDatabase : public ITestInterface<TestDatabase>
{
    Q_OBJECT
    $AsTest(TestDatabase)
public:
    TestDatabase();
    ~TestDatabase();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void test_demo();

};

