#pragma once

#include "core/util/IHeaderUtil.h"

$PackageWebCoreBegin

struct IHttpHeader
{
    friend class IResponseRaw;
public:
    void insert(IString key, IString value);
    void insert(IString key, const std::vector<IString>& value);
    void replace(IString key, IString value);
    void remove(const IString& key, const IString& value);
    void clear(const IString& key);
    std::vector<IStringView> keys() const;
    const std::vector<IString>& values(const IString& key) const;
    const IString& value(const IString& key) const;
    bool contain(const IString& key) const ;
    bool isEmpty() const;

public:
    inline static const IString Location = "Location";  // i hope this could be constexpr
    inline static const IString ContentLength = "Content-Length";
    inline static const IString ContentType = "Content-Type";
    inline static const IString ContentDisposition = "Content-Disposition";
    inline static const IString ContentTransferEncoding = "Content-Transfer-Encoding";
    inline static const IString Cookie = "Cookie";
    inline static const IString SetCookie = "Set-Cookie";

public:
    std::unordered_map<IString, std::vector<IString>> m_header;
};

$PackageWebCoreEnd
