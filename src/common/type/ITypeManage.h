#pragma once

#include "base/IHeaderUtil.h"

$PackageWebCoreBegin

class ITypeManage
{
    $UseInstance(ITypeManage)
public:
    ITypeManage() = default;

    static void registerBeanType(const QString& typeName);
    static void registerNamespace(const QString& nmspace);
    static bool containBean(const QString& typeName);

private:
    QStringList m_beanNames;
    QStringList m_nameSpaces;
};

$PackageWebCoreEnd
