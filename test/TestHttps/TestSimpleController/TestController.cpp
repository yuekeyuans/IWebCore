﻿#define $SourceFile

#include "TestController.h"

TestController::TestController()
{

}

IRendererResponse TestController::hello()
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
    return  IRedirectResponse("http://www.baidu.com");
}
