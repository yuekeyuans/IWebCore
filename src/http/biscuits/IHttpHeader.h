#pragma once

#include "core/util/IHeaderUtil.h"

$PackageWebCoreBegin

struct IHttpHeader
{
public:
    void insert(IString key, IString value);
    void replace(IString key, IString value);
    void remove(IString key, IString value);
    void clear(IString key);
    std::vector<IString> keys() const;
    const std::vector<IString>& values(const IString& key) const;
    const IString& value(const IString& key) const;
    bool hasKey(const IString& key) const ;

public:
    inline static const IString Location = "Location";  // i hope this could be constexpr
    inline static const IString ContentLength = "Content-Length";
    inline static const IString ContentType = "Content-Type";
    inline static const IString ContentDisposition = "Content-Disposition";
    inline static const IString ContentTransferEncoding = "Content-Transfer-Encoding";
    inline static const IString Cookie = "Cookie";
    inline static const IString SetCookie = "Set-Cookie";

private:
    inline static const IString Empty {};
    inline static const std::vector<IString> EmptyVector {};

private:
    std::unordered_map<IString, std::vector<IString>> m_header;
};

$PackageWebCoreEnd
