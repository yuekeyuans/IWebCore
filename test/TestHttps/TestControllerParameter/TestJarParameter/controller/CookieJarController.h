#pragma once

#include <IWebCore>

class CookieJarController : public IControllerInterface<CookieJarController>
{
    Q_GADGET
    $AsController(CookieJarController, cookie)
public:
    CookieJarController() = default;

    $GetMapping(requestCookies)
    QString requestCookies(ICookieJar& jar);

    $GetMapping(getRequestCookie)
    QString getRequestCookie(const ICookieJar& jar);

    $GetMapping(hasRequestCookie)
    QString hasRequestCookie(ICookieJar& jar);

    $GetMapping(addResponseCookie1)        
    QString addResponseCookie1(ICookieJar& jar);
};
