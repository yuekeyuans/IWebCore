#include "CookieJarController.h"


QString CookieJarController::addResponseCookie1(ICookieJar& jar)
{
    jar.addResponseCookie("hello", "world");
    return "hello world";
}

QString CookieJarController::hasResponseCookie(ICookieJar &jar)
{
    jar.hasResponseCookie()
    jar.addResponseCookie("hello", "world");
    return "hello world";
}
