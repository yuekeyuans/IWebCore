#pragma once

#include <IWebCore>

class HelloController : public IControllerInterface<HelloController>
{
    Q_GADGET
    $AsController(HelloController)
public:
    HelloController();

    $GetMapping(getHello, hello)
    QString getHello();

};

