#pragma once

#include <QObject>

class TestOrmPrimaryKey : public QObject
{
    Q_OBJECT
public:
    TestOrmPrimaryKey();
    ~TestOrmPrimaryKey() = default;

private slots:
    void init();
};
