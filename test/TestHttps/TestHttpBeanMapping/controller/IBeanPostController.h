#pragma once

#include <IWebCore>

#include "UserBean.h"

class IBeanPostController : public IControllerInterface<IBeanPostController>
{
    Q_GADGET
    $AsController(IBeanPostController, beanPost)
public:
    IBeanPostController();

    // url , header, param 已经在 get 当中测过，现在主要是测试 body 当中的数据

    $PostMapping(postMultiPart, multipart)
    QString postMultiPart(IRequest& request, $Content(UserBean, bean));

    $PostMapping(postUrlEncoded, urlEncoded)
    QString postUrlEncoded(IRequest& request, $Content(UserBean, bean));


    $PostMapping(postJsonValue, jsonvalue)
    QString postJsonValue(IRequest& request, $Content(UserBean, bean));


    $IgnoreParamWarn(postMixed1)
    $PostMapping(postMixed1, mixed1/<name:string>)
    QString postMixed1(IRequest& request, UserBean bean);

    $IgnoreParamWarn(postMixed2)
    $PostMapping(postMixed2, mixed2/<name:string>)
    QString postMixed2(IRequest& request, UserBean bean);

};

