#pragma once

#include "IWeb/IControllerInterface"

class TestController : public IControllerInterface<TestController, true>
{
    Q_GADGET
    $AsController(TestController)
public:
    TestController();

    $GetMapping(hello, /)
    QString hello();

    $PostMapping(helloGet, hello)
    QString helloGet(){
        return "";
    }

    $GetMapping(index, hello/index)
    IFileResponse index();
};

