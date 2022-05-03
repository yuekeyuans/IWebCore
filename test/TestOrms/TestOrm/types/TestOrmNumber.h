#pragma once

#include <IWebCore>
#include <QtTest>
#include "NumberBean.h"
#include "NumberModel.h"

class TestOrmNumber : public QObject
{
    Q_OBJECT
public:
    TestOrmNumber();
    ~TestOrmNumber() = default;

private slots:
    void init();
    void testInsertFind();

private:
    NumberModel model;
};

