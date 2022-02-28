#pragma once

#include <IWebCore>
#include <QtTest>

class TestConfig : public QObject
{
    Q_OBJECT
public:
    TestConfig();

private slots:
    void init();
    void test1();

};

