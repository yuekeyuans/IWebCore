#include "TestController.h"

TestController::TestController()
{

}

QString TestController::hello()
{
    return QStringLiteral("hello world");
}

IFileResponse TestController::index()
{
    return "index.html";
}
