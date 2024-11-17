#pragma once

#include <IHttp/IHttpControllerInterface>
#include "bean/StudentBean.h"

class ReturnTypeController : public IHttpControllerInterface<ReturnTypeController, true>
{
    Q_GADGET
    $AsController(ReturnTypeController)
public:
    ReturnTypeController();

public:
    $GetMapping(qstring)
    QString qstring(){
        return "hello world";
    }
};

