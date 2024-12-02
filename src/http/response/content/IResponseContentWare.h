#pragma once

#include "core/util/IHeaderUtil.h"

$PackageWebCoreBegin

class IRequest;
class IResponseContentWare
{
    friend class IResponseRaw;
public:
    IResponseContentWare() = default;
    virtual ~IResponseContentWare();

    IResponseContentWare(const QByteArray& byteArray);
    IResponseContentWare(QByteArray&& byteArray) noexcept;
    IResponseContentWare(const std::string& stdString);
    IResponseContentWare(std::string&& stdString) noexcept;
    IResponseContentWare(IStringView stringView);
    IResponseContentWare(IString&&);
    IResponseContentWare(const IString&);

public:
    virtual IStringView getContent();

public:
    IString m_dataRaw;
};

$PackageWebCoreEnd
