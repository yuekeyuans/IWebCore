#pragma once

#include "core/util/IHeaderUtil.h"
#include "ITypeNode.h"
#include <functional>

$PackageWebCoreBegin

class IRequest;
struct IReturnTypeNode : public ITypeNode
{
public:
    IReturnTypeNode() = default;
    IReturnTypeNode(QMetaType::Type, const QString& name);
    void* create() const;
    void destroy(void*ptr) const;
    void resolveValue(IRequest& request, void* ptr) const;

private:
    std::function<void*()> m_createFun{};
    std::function<void(void*)> m_destroyFun{};
    std::function<void(IRequest&, void*)> m_resolveFun{};
};

$PackageWebCoreEnd
