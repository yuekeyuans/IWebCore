#pragma once

#include <IHttp/IHttpControllerInterface>

class UrlController : public IHttpControllerInterface<UrlController>
{
    Q_GADGET
    $AsController(UrlController)
public:
    UrlController();

    $GetMapping(index, /)
    QString index(){
        return "hello";
    }

    $GetMapping(hello, helloWorld)
    QString hello(){
        return "hello";
    }

    $GetMapping(hello1, hello/<world>)
    QString hello1(){
        return "hello";
    }
    $GetMapping(helloInt, hello/<world|double>)
    QString helloInt(){
        return "hello";
    }
    $GetMapping(helloIntAnomyous, hello/<|int>)
    QString helloIntAnomyous(){
        return "hello";
    }
    $GetMapping(helloIntAnomyous1, hello/world/<a|int>)
    QString helloIntAnomyous1(){
        return "hello";
    }

    $GetMapping(helloIntAnomyous2, hello/<path||(\\w+)>)
    QString helloIntAnomyous2(){
        return "hello";
    }

    $GetMapping(helloIntAnomyous3, hello/&d)
    QString helloIntAnomyous3(){
        return "hello";
    }
};

