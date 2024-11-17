#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/unit/ISingletonUnit.h"
#include "http/base/IMetaType.h"

$PackageWebCoreBegin

class IRequest;
class IMethodParameterManage : public ISingletonUnit<IMethodParameterManage>
{
    using CreateReturnFun = std::function<void*()>;
    using DestroyReturnFun = std::function<void(void*ptr)>;
public:
    IMethodParameterManage();
};

$PackageWebCoreEnd
