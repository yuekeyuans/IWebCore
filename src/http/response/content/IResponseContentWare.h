#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/base/IString.h"

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
    virtual int getSize();
    virtual IStringView getContent();
    virtual const std::string& getType() const = 0;
    virtual const std::string& getSuggestedMime() const = 0;

protected:
    IResponseContentWare* m_excess{};

public:
    IString m_dataRaw;
};

$PackageWebCoreEnd
