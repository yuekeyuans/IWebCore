#pragma once

#include "core/util/IHeaderUtil.h"

$PackageWebCoreBegin

struct IHttpHeader
{
    friend class IResponseRaw;
public:
    void insert(IString key, IString value);
    void remove(const IString& key);
    std::vector<IStringView> keys() const;
    const IString& value(const IString& key) const;
    bool contain(const IString& key) const;
    bool isEmpty() const;

public:
    inline static const IString Allow = "Allow";
    inline static const IString Connection = "Connection";
    inline static const IString ContentLength = "Content-Length";
    inline static const IString ContentType = "Content-Type";
    inline static const IString Cookie = "Cookie";
    inline static const IString ContentDisposition = "Content-Disposition";
    inline static const IString ContentTransferEncoding = "Content-Transfer-Encoding";
    inline static const IString KeepAlive = "Keep-Alive";
    inline static const IString Location = "Location";  // i hope this could be constexpr
    inline static const IString SetCookie = "Set-Cookie";
    inline static const IString TransferEncoding = "Transfer-Encoding";

public:
    std::unordered_map<IString, IString> m_header;  // TODO: 这个改成 IStringView,
};

$PackageWebCoreEnd
