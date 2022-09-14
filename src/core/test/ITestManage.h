#pragma once

#include "base/IHeaderUtil.h"

// TODO: 这里可以再改进，但是也没多大必要
class ITestManage
{
    $UseInstance(ITestManage)
private:
    ITestManage() = default;

public:
    static void registerTestClass(QObject* obj);
    static void invokeAllTestClass();

private:
    QVector<QObject*> m_objs;
};
