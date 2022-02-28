#include "HttpMethodController.h"

HttpMethodController::HttpMethodController()
{
}

IPlainTextResponse HttpMethodController::testGet()
{
    return "hello world test get";
}

IPlainTextResponse HttpMethodController::testPut()
{
    return "hello world test put";
}
