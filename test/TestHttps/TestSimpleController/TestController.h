#pragma once

#include "IWeb/IControllerInterface"

class TestController : public IControllerInterface<TestController>
{
    Q_GADGET
    $AsController(TestController)
public:
    TestController();

};

