﻿#pragma once

#include <IWebCore>

class CookieJarController : public IControllerInterface<CookieJarController, false>
{
    Q_GADGET
    $AsController(CookieJarController, cookie)
public:
    CookieJarController() = default;

/////////////////////////////////////
// request
/////////////////////////////////////

    $GetMapping(requestCookies)
    QString requestCookies(ICookieJar& jar);

    $GetMapping(getRequestCookie)
    QString getRequestCookie(ICookieJar& jar);

    $GetMapping(getRequestCookies)
    QString getRequestCookies(const ICookieJar& jar);

    $GetMapping(getRequestCookieValue)
    QString getRequestCookieValue(const ICookieJar& jar);

    $GetMapping(getRequestCookieValues)
    QString getRequestCookieValues(const ICookieJar& jar);

    $GetMapping(hasRequestCookie)
    QString hasRequestCookie(ICookieJar& jar);

    $GetMapping(deleteRequestCookie)
    QString deleteRequestCookie(ICookieJar& jar);

/////////////////////////////////////
// response
/////////////////////////////////////
    $GetMapping(addResponseCookie1)
    QString addResponseCookie1(ICookieJar& jar);

    $GetMapping(responseCookies)
    QString responseCookies(ICookieJar& jar);

/////////////////////////////////////
// cookie-part
/////////////////////////////////////

    $GetMapping(cookiePartTest)
    QString cookiePartTest(ICookiePart hello);

    $GetMapping(cookiePartRefTest)
    QString cookiePartRefTest(const ICookiePart& hello);

//////////////////////////////////////////
// cookie value
//////////////////////////////////////////

    $GetMapping(cookieValueTest)
    QString cookieValueTest($Cookie(const QString&, hello));

};
