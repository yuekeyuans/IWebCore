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

IByteArrayResponse TestController::index()
{
    return "index.html";
//    return  IRedirectResponse("http://www.baidu.com");
}
