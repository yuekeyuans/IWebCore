#pragma once

#include "core/base/IHeaderUtil.h"

$PackageWebCoreBegin

class IBeanTypeManagePrivate;
class IBeanTypeManage
{
    $UseInstance(IBeanTypeManage)
    $UseDataPtr(IBeanTypeManage)
private:
    IBeanTypeManage();

public:
    static void registerBeanType(const QString& typeName);
    static void registerNamespace(const QString& nmspace);
    static bool containBean(const QString& typeName);
};

$PackageWebCoreEnd
