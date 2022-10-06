#include "CookieJarController.h"


QString CookieJarController::addResponseCookie1(ICookieJar& jar)
{
    jar.addResponseCookie("hello", "world");
    return "hello world";
}

QString CookieJarController::hasResponseCookie(ICookieJar &jar)
{
    if(jar.containRequestCookieKey("hello")){
        return "exist";
    }else{
        return "not exist";
    }
}
