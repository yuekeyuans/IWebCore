#pragma once

#include <IWebCore>
#include <QtTest>

class TestFunctionCallConfiger : public QObject
{
    Q_OBJECT
public:
    TestFunctionCallConfiger() = default;

    $IntConfiger(connections, server.max_connections);

    $DoubleConfiger(port, server.com_port);

    $BoolConfiger(enabled, services._0.enabled);

    $StringConfiger(name, services._1.name);

private slots:
    void test_1();

    void test_SystemValue();

};

