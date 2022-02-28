#pragma once

#include <IWebCore>

class TestDatabase : public QObject
{
    Q_OBJECT
public:
    TestDatabase();
    ~TestDatabase();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void test_demo();

};

