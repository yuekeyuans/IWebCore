#define $SourceFile

#include "TestController.h"

TestController::TestController()
{

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
