#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/unit/ISingletonUnit.h"
#include "http/base/ITypeNode.h"

$PackageWebCoreBegin

class IRequest;
class IMethodParameterManage : public ISingletonUnit<IMethodParameterManage>
{
    using CreateReturnFun = std::function<void*()>;
    using DestroyReturnFun = std::function<void(void*ptr)>;

public:
    IMethodParameterManage();

public:
    void registCreateReturnFun(ITypeNode node, CreateReturnFun);
    void registDestroyReturnFun(ITypeNode node, DestroyReturnFun);

public:
    QMap<ITypeNode, CreateReturnFun> m_createReturnFun{};
    QMap<ITypeNode, DestroyReturnFun> m_destroyReturnFun{};
};

$PackageWebCoreEnd
