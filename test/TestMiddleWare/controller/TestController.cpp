#include "TestController.h"

TestController::TestController()
{
}

QString TestController::index()
{
    return "hello world";
}

QString TestController::cookie(ICookie &cookie)
{
    cookie.setCookie("hello", "world", 12000);
    return "cookie test";
}
