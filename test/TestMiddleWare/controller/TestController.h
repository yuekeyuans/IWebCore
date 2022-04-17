#pragma once

#include <IWebCore>

class TestController : public IControllerInterface<TestController>
{
    Q_GADGET
    $AsController(TestController)
public:
    TestController() = default;

    $GetMapping(index, /)
    QString index();

    $GetMapping(cookie, /cookie)
    QString cookie(ICookieJar& cookie);

    $GetMapping(testCookiePart, /cookiePart)
    QString testCookiePart(ICookieJar& cookie);
};

