#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/test/ITestManageBaseInterface.h"

$PackageWebCoreBegin

class IHttpTestManage : public ITestManageBaseInterface<IHttpTestManage>
{
public:
    IHttpTestManage() = default;

public:
//    void invokeTests();
};

//inline void IHttpTestManage::invokeTests()
//{
//    qDebug() << __FUNCDNAME__;
//}

$PackageWebCoreEnd
