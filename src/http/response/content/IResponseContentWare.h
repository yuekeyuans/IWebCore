#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/base/IStringData.h"

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

public:
    virtual int getSize();
    virtual IStringView getContent();
    virtual IStringView getType() = 0;
    virtual IStringView getSuggestedMime() = 0;

protected:
    IResponseContentWare* m_excess{};

public:
    IStringData m_dataRaw;
};

$PackageWebCoreEnd
