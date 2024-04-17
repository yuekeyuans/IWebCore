#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/unit/ISingletonUnit.h"

$PackageWebCoreBegin

class ITestManage : public ISingletonUnit<ITestManage>
{
public:
    ITestManage() = default;

public:
    static void registerTestClass(QObject* obj);
    static void invokeAllTestClass();

private:
    QVector<QObject*> m_objs;
};


$PackageWebCoreEnd
