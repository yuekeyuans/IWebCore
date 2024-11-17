#pragma once

#include "core/util/IHeaderUtil.h"
#include "IMetaType.h"
#include <functional>

$PackageWebCoreBegin

class IRequest;
struct IReturnType : public IMetaType
{
    friend class IReturnTypeDetail;
public:
    IReturnType() = default;
    void* create() const;
    void destroy(void*ptr) const;
    void resolveValue(IRequest& request, void* ptr) const;
};

$PackageWebCoreEnd
