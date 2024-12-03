#pragma once

#include "core/util/IHeaderUtil.h"

$PackageWebCoreBegin

class IRequest;
class IResponseContent
{
    friend class IResponseRaw;
    enum class Type{
        IString,
        File,
        Invalid
    };
public:
    IResponseContent() = default;
    virtual ~IResponseContent();

    IResponseContent(const char*);
    IResponseContent(const QByteArray& byteArray);
    IResponseContent(QByteArray&& byteArray) noexcept;
    IResponseContent(const std::string& stdString);
    IResponseContent(std::string&& stdString) noexcept;
    IResponseContent(IStringView stringView);
    IResponseContent(IString&&);
    IResponseContent(const IString&);

public:
    virtual IStringView getContent();

public:
    Type m_type{Type::IString};
    IString m_dataRaw{};
};

$PackageWebCoreEnd
