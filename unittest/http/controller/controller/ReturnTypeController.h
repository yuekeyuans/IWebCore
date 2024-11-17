#pragma once

#include <IHttp/IHttpControllerInterface>
#include "bean/StudentBean.h"

class ReturnTypeController : public IHttpControllerInterface<ReturnTypeController, true>
{
    Q_GADGET
public:
    ReturnTypeController();

public:
    $GetMapping(index)
    QString index(){
        return "hello world";
    }
};

