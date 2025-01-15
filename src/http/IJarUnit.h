#pragma once

#include "core/util/IHeaderUtil.h"

$PackageWebCoreBegin

class IRequestImpl;
class IJarUnit
{
public:
    IJarUnit() = delete;
    ~IJarUnit() = default;
    IJarUnit(const IJarUnit&) = delete;
    IJarUnit(IJarUnit&&) = delete;
    IJarUnit& operator =(const IJarUnit&) = delete;
    IJarUnit& operator =(IJarUnit&&) = delete;

    IJarUnit(IRequestImpl& impl) : m_impl(impl){}

protected:
    IRequestImpl& m_impl;
};

$PackageWebCoreEnd
