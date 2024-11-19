﻿#pragma once

#include <QtCore>
#include <QtTest>
#include <DataBean.h>

class TestConfig : public ITestTaskInterface<TestConfig>
{
    Q_OBJECT
    $AsTest(TestConfig)
public:
    TestConfig();

private slots:
    void init();
    void test_1();
    void test_dataSource();
    void test_dataSource1();
};

