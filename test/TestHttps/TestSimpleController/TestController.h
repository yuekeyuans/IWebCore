#pragma once

#include "IWeb/IControllerInterface"
#include "web/response/IByteArrayResponse.h"
#include "web/response/IRendererResponse.h"

class TestController : public IControllerInterface<TestController, true>
{
    Q_GADGET
//    $AsControl ler(TestController)
public:
    TestController();

////    $DeleteMapping(helloDelete, /)
//    QString helloDelete($Header(QString, name));

//    $GetMapping(hello, /)
    IRendererResponse hello();

////    $PostMapping(helloGet, hello)
//    QString helloGet(){
//        return "";
//    }

    $GetMapping(index, hello/index1)
    IFileResponse index();
};

