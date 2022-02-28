#pragma once

#include <IWebCore>
#include <QtTest>

/**
 * @brief 测试 QList, QVector, QMap 中 bean 的构造。
 */
class TestBeanListMapConvertion : public QObject
{
    Q_OBJECT
public:
    TestBeanListMapConvertion() = default;

private slots:
    void test_Bean();
    void test_QListBean();
    void test_normalContainer();
};
