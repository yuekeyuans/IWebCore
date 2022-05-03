#pragma once

#include <IWebCore>

#include "UserBean.h"

class IBeanGetController : public IControllerInterface<IBeanGetController>
{
    Q_GADGET
    $AsController(IBeanGetController, bean)
    $IgnoreAllParamWarn()
public:
    IBeanGetController();

    $GetMapping(getParamBean, getBean)
    QString getParamBean($Param(UserBean, bean));

    $GetMapping(getUrlBean, <name:string>/<home:string>/<age:int>/<birthDate:date>)
    QString getUrlBean($Url(UserBean, bean));

    $GetMapping(getHeaderBean, headerGet)
    QString getHeaderBean($Header(UserBean, bean));

    $GetMapping(getMixedBean1, mixed1/<name:string>)
    QString getMixedBean1(UserBean bean);
};

