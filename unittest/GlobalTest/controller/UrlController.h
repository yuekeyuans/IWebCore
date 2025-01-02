#pragma once

#include <IHttp/IHttpControllerInterface>

class UrlController : public IHttpControllerInterface<UrlController>
{
    Q_GADGET
    $AsController(UrlController)
public:
    UrlController();

    $GetMapping(hello, helloWorld)
    QString hello(){
        return "hello";
    }
};

