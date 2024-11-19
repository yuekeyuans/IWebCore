#pragma once

#include <IWebCore>

$EnableCatagory(Test)
class TestDatabase : public ITestTaskInterface<TestDatabase>
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

