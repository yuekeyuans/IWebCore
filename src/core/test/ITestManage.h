#pragma once

#include "core/base/IHeaderUtil.h"

class ITestManage
{
private:
    ITestManage() = default;
    static ITestManage* instance();

public:
    static void registerTestClass(QObject* obj);
    static void invokeAllTestClass();

private:
    QVector<QObject*> m_objs;
};
