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

    $GetMapping(hello1, hello/<world>)
    QString hello1(){
        return "hello";
    }
    $GetMapping(helloInt, hello/<world|int>)
    QString helloInt(){
        return "hello";
    }
    $GetMapping(helloIntAnomyous, hello/<|int>)
    QString helloIntAnomyous(){
        return "hello";
    }
    $GetMapping(helloIntAnomyous1, hello/world/<>)
    QString helloIntAnomyous1(){
        return "hello";
    }

    $GetMapping(helloIntAnomyous2, hello/<path||(\w+)>)
    QString helloIntAnomyous2(){
        return "hello";
    }

    $GetMapping(helloIntAnomyous3, hello/?d)
    QString helloIntAnomyous3(){
        return "hello";
    }
};

