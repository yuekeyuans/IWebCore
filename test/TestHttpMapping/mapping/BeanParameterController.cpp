#include "BeanParameterController.h"


QString BeanParameterController::testBean($Param(TestBean, bean))
{
    return bean_param;
}

QString BeanParameterController::testBeanRef(TestBean &bean, IRequest &request)
{
    Q_UNUSED(request);
    return bean;
}

QString BeanParameterController::testInvalidBean(A a)
{
    Q_UNUSED(a);
    return "invalid";
}
