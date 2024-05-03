#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/unit/ISingletonUnit.h"

$PackageWebCoreBegin

class IBeanTypeManage : public ISingletonUnit<IBeanTypeManage>
{
public:
    IBeanTypeManage() = default;

public:
    static void registerBeanType(const QString& typeName);
    static bool containBean(const QString& typeName);

private:
    QStringList m_beanNames;
};

$PackageWebCoreEnd

