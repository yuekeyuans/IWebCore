#pragma once

#include "base/IHeaderUtil.h"

// TODO: 这个 文件在之后需要改名，应该和 bean 相关

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
