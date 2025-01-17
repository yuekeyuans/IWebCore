﻿#pragma once

#include "core/util/IHeaderUtil.h"
#include "http/ICookiePart.h"
#include "http/IJarUnit.h"
#include <chrono>

$PackageWebCoreBegin

class ICookieJar : public IJarUnit
{
public:
    using IJarUnit::IJarUnit;

public:
    const QMultiHash<IStringView, IStringView>& requestCookies() const;
    ICookiePart getRequestCookie(IString key) const;
    QList<ICookiePart> getRequestCookies(const IString& key) const;

    IStringViewList requestCookieKeys() const;

    bool containRequestCookieKey(const IString& key) const;

    void deleteRequestCookies(const IString& key);

    // response
    std::list<ICookiePart>& responseCookies();
    const std::list<ICookiePart>& responseCookies() const;
    ICookiePart getResponseCookie(const IString& key) const;
    QList<IString> responseCookieKeys() const;
    bool containResponseCookieKey(const IString& key) const;
    void deleteResponseCookie(const IString& key);

    template<typename T>        // in latter c++14, you can pass 1h, 24h type.
    void addResponseCookie(IString key, IString value, std::chrono::duration<T> duration, bool secure=false, bool httpOnly=false);
    void addResponseCookie(ICookiePart cookiePart);
    void addResponseCookie(IString key, IString value);
    void addResponseCookie(IString key, IString value, int maxAge, bool secure=false, bool httpOnly=false);
    void addResponseCookie(IString key, IString value, QDateTime expires, bool secure=false, bool httpOnly=false);
};

template<typename T>
void ICookieJar::addResponseCookie(IString key, IString value, std::chrono::duration<T> duration, bool secure, bool httpOnly)
{
    ICookiePart part(std::move(key), std::move(value), duration, secure, httpOnly);
    addResponseCookie(std::move(part));     // TODO: test whether move works
}

$PackageWebCoreEnd
