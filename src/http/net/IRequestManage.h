#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/unit/ISingletonUnit.h"
#include <unordered_set>

$PackageWebCoreBegin

class IRequest;

class IRequestManage : public ISingletonUnit<IRequestManage>
{
public:
    IRequestManage();

public:
    void pushRequest(IRequest*);
    void popRequest(IRequest*);

private:
    std::unordered_set<IRequest*> m_requests;
};

$PackageWebCoreEnd
