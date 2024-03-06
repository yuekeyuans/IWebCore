#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/unit/ISingletonUnit.h"

$PackageWebCoreBegin

class IBeanTypeManagePrivate;
class IBeanTypeManage : public ISingletonUnit<IBeanTypeManage>
{
    $UseDataPtr(IBeanTypeManage)
public:
    IBeanTypeManage();

    // TODO: 这里之后检查， 使用 typename 获取名称
public:
    static void registerBeanType(const QString& typeName);
    static bool containBean(const QString& typeName);
};

$PackageWebCoreEnd

#include "IBeanTypeManage.cpp"
