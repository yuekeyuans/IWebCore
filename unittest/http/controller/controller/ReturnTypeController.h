#pragma once

#include <IHttp/IHttpControllerInterface>
#include "bean/StudentBean.h"

class ReturnTypeController : public IHttpControllerInterface<ReturnTypeController>
{
    Q_GADGET
    $AsController(ReturnTypeController)
public:
    ReturnTypeController();

    $GetMapping(beanGet)
    StudentBean beanGet(){
        return StudentBean();
    }

};

