#pragma once

#include <IWebCore>
#include <QtTest>

class TestGadget : public ITestInterface<TestGadget>
{
    Q_OBJECT
    $AsTest(TestGadget)
public:
    TestGadget();

private slots:
    void init();
    void test_Registration();
    void test_typeManageRegistration();
    void test_method();
    void test_className();
    void test_clone();

    void test_Initialized();
};

