#pragma once

#include <IWebCore>
#include <QtTest>
#include "ViewBean.h"
#include "ViewModel.h"

class TestView : public QObject
{
    Q_OBJECT
public:
    TestView();

private slots:
    void test_viewFind();

private:
    ViewModel model;
};

