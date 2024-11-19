#pragma once

#include "IWeb/IControllerInterface"

class TestController : public IControllerInterface<TestController>
{
    Q_GADGET
public:
    TestController();

    $GetMapping(test, test)
    QString test();
};

