#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/unit/ISingletonUnit.h"

$PackageWebCoreBegin

class ITestManage : public ISingletonUnit<ITestManage>
{
public:
    ITestManage() = default;

public:
    void registerTestClass(QObject* obj);
    void invokeAllTestClass();

private:
    QVector<QObject*> m_objs;
};


$PackageWebCoreEnd
