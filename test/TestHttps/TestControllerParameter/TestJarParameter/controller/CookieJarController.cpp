#include "CookieJarController.h"

QString CookieJarController::requestCookies(ICookieJar &jar)
{
    auto map = jar.requestCookies();
    return IJsonUtil::toString(map);
}

QString CookieJarController::getRequestCookie(ICookieJar &jar)
{
    bool ok;
    auto cookie = jar.getRequestCookie("hello", ok);
    if(!ok){
        return "exist error";
    }
    return cookie.toHeaderString();
}

QString CookieJarController::getRequestCookies(const ICookieJar &jar)
{
    QStringList ret;
    auto cookies = jar.getRequestCookies("hello");
    for(const auto& cookie : cookies){
        ret.append(cookie.toHeaderString());
    }
    return ret.join(", ");
}

QString CookieJarController::getRequestCookieValue(const ICookieJar &jar)
{
    bool ok;
    auto cookie = jar.getRequestCookieValue("hello", ok);
    if(!ok){
        return "cookie error";
    }

    return cookie;
}

QString CookieJarController::getRequestCookieValues(const ICookieJar &jar)
{
    QString key = "hello";
    auto cookies = jar.getRequestCookieValues("hello");
    if(!cookies.isEmpty()){
        return key + " " + cookies.join(", ");
    }

    return "not exist";
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

