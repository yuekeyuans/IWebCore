#pragma once

#include <IWebCore>
#include <QtTest>

class TestBeanListMapConvertion : public IUnitTestInterface<TestBeanListMapConvertion>
{
    Q_OBJECT
public:
    TestBeanListMapConvertion() = default;

private slots:
    void test_Bean();
    void test_QListBean();
    void test_normalContainer();
};
