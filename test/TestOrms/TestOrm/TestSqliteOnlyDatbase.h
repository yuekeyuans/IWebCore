#pragma once

#include <IWebCore>
#include <QtTest>
#include "PhoneBean.h"
#include "SqliteModel.h"

class TestSqliteOnlyDatbase : public QObject
{
    Q_OBJECT
public:
    TestSqliteOnlyDatbase();
private slots:
    void init();
    void test1();

private:

private:
    SqliteModel model;
};

