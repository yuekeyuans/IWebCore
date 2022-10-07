#include "CookieJarController.h"

QString CookieJarController::requestCookies(ICookieJar &jar)
{
    auto map = jar.requestCookies();
    return IJsonUtil::toString(map);
}

QString CookieJarController::hasRequestCookie(ICookieJar &jar)
{
    if(jar.containRequestCookieKey("hello")){
        return "exist";
    }else{
        return "not exist";
    }
}

QString CookieJarController::addResponseCookie1(ICookieJar& jar)
{
    jar.addResponseCookie("hello", "world");
    return "hello world";
}

