#pragma once

#include <IWebCore>
#include <QtTest>

#include "OneBean.h"

class TestGadget : public QObject
{
    Q_OBJECT
public:
    TestGadget();

private slots:
    void init();
    void test_Registration();
    void test_method();
    void test_className();
    void test_clone();

    void test_Initialized();
};

