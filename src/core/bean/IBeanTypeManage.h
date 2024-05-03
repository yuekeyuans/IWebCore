#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/unit/ISingletonUnit.h"

$PackageWebCoreBegin

class IBeanTypeManageImpl;
class IBeanTypeManage : public ISingletonUnit<IBeanTypeManage>
{
    $UseDataPtr(IBeanTypeManage)
public:
    IBeanTypeManage();

public:
    static void registerBeanType(const QString& typeName);
    static bool containBean(const QString& typeName);
};

$PackageWebCoreEnd

