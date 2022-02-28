#pragma once

#include <IWebCore>
#include <QtTest>
#include "DataBean.h"
#include "sqlite/SqliteModel.h"

class TestSqliteDb : public QObject
{
    Q_OBJECT
public:
    TestSqliteDb();

private slots:
    void init();
    void insertAndFetch();

private:
    SqliteModel model;
};

