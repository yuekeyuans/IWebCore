#include "IArgumentType.h"

$PackageWebCoreBegin

void *IArgumentType::create(IRequest & request) const
{
    return m_createFun(request);
}

void IArgumentType::destory(void *ptr) const
{
    return m_destroyFun(ptr);
}

$PackageWebCoreEnd
