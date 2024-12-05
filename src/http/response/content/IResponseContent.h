#pragma once

#include "core/util/IHeaderUtil.h"

$PackageWebCoreBegin

class IResponseRaw;
class IResponseContent
{
    friend class IResponseRaw;
public:
    IResponseContent() = default;
    virtual ~IResponseContent();

    IResponseContent(IString&&);
    IResponseContent(const IString&);

public:
    IString m_dataRaw{};
    std::function<void(IResponseRaw&)> m_function{nullptr};
};

$PackageWebCoreEnd
