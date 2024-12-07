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
    void setAttribute(IString, IString);

public:
    IString m_content{};
    std::function<void(const IResponseContent&, IResponseRaw&)> m_function{nullptr};
    QMap<IString, IString>* m_attribute{nullptr};
};

$PackageWebCoreEnd
