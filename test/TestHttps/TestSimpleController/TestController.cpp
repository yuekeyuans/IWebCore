#include "TestController.h"

TestController::TestController()
{

}

QString TestController::hello()
{
    return QStringLiteral("hello world");
}

IStaticFileResponse TestController::index()
{
    return "index.html";
}
