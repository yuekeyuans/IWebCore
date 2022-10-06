#pragma once

#include <IWebCore>

class CookieJarController : public IControllerInterface<CookieJarController>
{
    Q_GADGET
    $AsController(CookieJarController, cookie)
public:
    CookieJarController() = default;

    $GetMapping(addResponseCookie1)
    QString addResponseCookie1(ICookieJar& jar);

    $GetMapping(hasResponseCookie)
    QString hasResponseCookie(ICookieJar& jar);
};
