#pragma once

#include <IWebCore>
#include <QtTest>

#include "OneTable.h"

class TestTable : public QObject
{
    Q_OBJECT
public:
    TestTable();

private slots:
    void init();
    void test_demo();
};

