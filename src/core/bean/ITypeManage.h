#pragma once

#include "base/IHeaderUtil.h"

$PackageWebCoreBegin

class IBeanTypeManagePrivate;
class IBeanTypeManage
{
    $UseInstance(IBeanTypeManage)
    $UseDataPtr(IBeanTypeManage)
    Q_DISABLE_COPY_MOVE(IBeanTypeManage)
public:
    IBeanTypeManage();

    static void registerBeanType(const QString& typeName);
    static void registerNamespace(const QString& nmspace);
    static bool containBean(const QString& typeName);
};

$PackageWebCoreEnd
