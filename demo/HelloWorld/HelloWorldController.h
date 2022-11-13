#pragma once

#include <IWebCore>

class HelloWorldController : public IControllerInterface<HelloWorldController, true>
{
    Q_GADGET
    $AsController (HelloWorldController, hello)

public:
    HelloWorldController();

    $GetMapping (world)
    QString world();
};
