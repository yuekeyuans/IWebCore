#define $SourceFile true
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

QString CookieJarController::deleteRequestCookie(ICookieJar &jar)
{
    if(jar.containRequestCookieKey("hello")){
        jar.deleteRequestCookies("hello");
        return "deleted";
    }else{
        return "not exist";
    }
}

QString CookieJarController::responseCookies(ICookieJar &jar)
{
    jar.addResponseCookie("hello", "world");
//    jar.addResponseCookie("yue", "keyuan", 100);

    auto cookies = jar.responseCookies();
    return cookies.first().toHeaderString();
}


QString CookieJarController::addResponseCookie1(ICookieJar& jar)
{
    jar.addResponseCookie("hello", "world");
    return "hello world";
}

QString CookieJarController::cookiePartTest(ICookiePart hello)
{
    return hello.value;
}

QString CookieJarController::cookiePartRefTest(const ICookiePart &hello)
{
    return hello.value;
}

QString CookieJarController::cookieValueTest($Cookie (const QString&, hello))
{
    hello.end();
    return "";
}
