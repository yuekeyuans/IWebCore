#include "TestController.h"

QString TestController::index()
{
    return "hello world";
}

QString TestController::cookie(ICookieJar &cookie)
{
    cookie.addCookie("hello", "world", 12000);
    return "cookie test";
}

QString TestController::testCookiePart(ICookieJar &cookie)
{
    ICookiePart part;
    cookie.addCookie(part);
    return part.toHeaderString();
}
