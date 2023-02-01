#pragma once

#include <IControllerInterface>
#include "mapping/TestBean.h"

class A{};

class BeanParameterController : public IControllerInterface<BeanParameterController>
{
    Q_GADGET
    $AsController(BeanParameterController)
public:
    BeanParameterController() = default;

//    $IgnoreParamWarn(testBean)
    $GetMapping(testBean, testParamBean)
    QString testBean($Param(TestBean, bean));

    $IgnoreParamWarn(testBeanRef)
    $GetMapping(testBeanRef, testBeanRef)
    QString testBeanRef(TestBean& bean, IRequest& request);

//    $PostMapping(testInvalidBean, testInvalidBean)
    QString testInvalidBean(A a);
};

