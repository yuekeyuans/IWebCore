#pragma once

#include <IWebCore>
#include <QtTest>
#include "ViewBean.h"
#include "ViewModel.h"

class TestView : public ITestInterface<TestView>
{
    Q_OBJECT
    $AsTest(TestView)
public:
    TestView();

private slots:
    void test_viewFind();

private:
    ViewModel model;
};

