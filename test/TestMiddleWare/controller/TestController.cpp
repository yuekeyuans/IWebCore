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
//    qDebug() << cookie.keys() << cookie.values();
    cookie.setCookie("hello", "world");
    return "cookie test";
}
