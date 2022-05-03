#pragma once

#include <IWebCore>
#include <QtTest>

#include "TableModel.h"

class TestTable : public QObject
{
    Q_OBJECT
public:
    TestTable();

private slots:
    void init();
    void test_insert();

private:
    TableModel model;
};

