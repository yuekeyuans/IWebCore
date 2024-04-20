#pragma once

#include <IWebCore>
#include <QtTest>

class TestGadget : public IUnitTestInterface<TestGadget>
{
    Q_OBJECT
public:
    TestGadget() = default;

private slots:
    void init();
    void test_Registration();
    void test_typeManageRegistration();
    void test_method();
    void test_className();
    void test_clone();

    void test_Initialized();
};

