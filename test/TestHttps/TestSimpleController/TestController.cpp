#define $SourceFile

#include "TestController.h"

TestController::TestController()
{

}

INodyResponse TestController::hello()
{
    return {"index.yky", {}};
}

//QString TestController::helloDelete($Header(QString, name)){
//    return name;
//}

//QString TestController::hello()
//{
//    return QStringLiteral("hello world");
//}

IFileResponse TestController::index()
{
//    return "index.htm";
    return  IRedirectResponse("http://www.baidu.com");
}
