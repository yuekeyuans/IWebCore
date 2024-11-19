#include "MyController.h"

QString MyController::index()
{
    return "hello world";
}

QString MyController::hello(QString name)
{
    return "hello " + name;
}
