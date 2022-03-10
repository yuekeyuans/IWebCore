#pragma once

#include <IWebCore>

class TestController : public IControllerInterface<TestController>
{
    Q_GADGET
    $AsController(TestController)
public:
    TestController();

    $GetMapping(index, /)
    QString index();
};

